/***********************************************************************************************************************
 * Audio Converter
 * Copyright (C) 2017  Igor Lapin
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************************************************/

#include "wavtomp3converterthread.h"
#include <lame/lame.h>
#include <QFile>
#include <QFileInfo>
#include <wavdecoder.h>
#include <QDir>

const QString WavToMp3ConverterThread::TAG = "WavToMp3ConverterThread";

WavToMp3ConverterThread::WavToMp3ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath,
												 Settings settings, QObject *parent) :
	ConverterThread(sourceFilePaths, destDirPath, parent),
	m_settings(settings)
{}

void WavToMp3ConverterThread::run()
{
	m_totalFiles = m_sourceFilePaths.size();
	for (m_currentFileIndex = 0; m_currentFileIndex < m_sourceFilePaths.size(); m_currentFileIndex++) {
		m_currentFileProgress = 0;
		emit progressChanged(calculateProgress());

		auto lameGlobalFlags = lame_init();
		lame_set_brate(lameGlobalFlags, m_settings.bitrate);
		lame_set_quality(lameGlobalFlags, 2);
		if (lame_init_params(lameGlobalFlags) < 0) {
			qCritical("%s: lame_init_params failed", qPrintable(TAG));
			lame_close(lameGlobalFlags);
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}

		QFile wavFile(m_sourceFilePaths[m_currentFileIndex]);
		QFileInfo wavFileInfo(wavFile);
		if (!wavFile.open(QFile::ReadOnly)) {
			qCritical("%s: Can't open source WAV file: %s", qPrintable(TAG),
					  qPrintable(m_sourceFilePaths[m_currentFileIndex]));
			lame_close(lameGlobalFlags);
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}
		WavDecoder *wavDecoder = new WavDecoder(wavFile);
		if (!wavDecoder->init()) {
			qInfo("%s: WavDecoder::init failed", qPrintable(TAG));
			wavFile.close();
			lame_close(lameGlobalFlags);
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}
		lame_set_num_channels(lameGlobalFlags, wavDecoder->format().numberOfChannels);
		lame_set_in_samplerate(lameGlobalFlags, wavDecoder->format().sampleRate);
		auto mp3BufferSize = int(std::ceil(1.25 * BUFFER_SIZE / wavDecoder->format().dataBlockSize + 7200));
		auto mp3Buffer = new unsigned char[mp3BufferSize];

		QString mp3FilePath = m_destDirPath + QDir::separator() + wavFileInfo.baseName() + ".mp3";
		QFile mp3File(mp3FilePath);
		if (!mp3File.open(QFile::WriteOnly)) {
			qCritical("%s: Can't open destination MP3 file: %s", qPrintable(TAG), qPrintable(mp3FilePath));
			lame_close(lameGlobalFlags);
			delete[] mp3Buffer;
			delete wavDecoder;
			wavFile.close();
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}
		int bytesRead = 0;
		int totalBytesRead = 0;
		int bytesToWrite = 0;
		char buffer[BUFFER_SIZE];
		while ((bytesRead = wavDecoder->decode(buffer, BUFFER_SIZE)) > 0) {
			bytesToWrite = lame_encode_buffer_interleaved(lameGlobalFlags, (short int *) buffer,
														  bytesRead / wavDecoder->format().dataBlockSize, mp3Buffer,
														  mp3BufferSize);
			mp3File.write((char *) mp3Buffer, bytesToWrite);

			totalBytesRead += bytesRead;
			m_currentFileProgress = float(totalBytesRead) / wavFileInfo.size();
			emit progressChanged(calculateProgress());

			if (isInterruptionRequested()) {
				delete wavDecoder;
				delete[] mp3Buffer;
				mp3File.close();
				wavFile.close();
				lame_close(lameGlobalFlags);
				goto interruption_requested;
			}
		}
		bytesToWrite = lame_encode_flush(lameGlobalFlags, mp3Buffer, mp3BufferSize);
		mp3File.write((char *) mp3Buffer, bytesToWrite);

		m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], SUCCESS);
		emit convertionResultAdded(m_convertionResults.last());

		delete wavDecoder;
		delete[] mp3Buffer;
		mp3File.close();
		wavFile.close();
		lame_close(lameGlobalFlags);
	}
interruption_requested:;
}
