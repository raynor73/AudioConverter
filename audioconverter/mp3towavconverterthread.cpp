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

#include "mp3towavconverterthread.h"
#include <lame/lame.h>
#include <wavencoder.h>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <resampler.h>
#include <algorithm>
#include <QDebug>

const QString Mp3ToWavConverterThread::TAG = "Mp3ToWavConverterThread";

Mp3ToWavConverterThread::Mp3ToWavConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath,
												 Settings settings, QObject *parent) :
	ConverterThread(sourceFilePaths, destDirPath, parent),
	m_settings(settings)
{}

void Mp3ToWavConverterThread::run()
{
	m_totalFiles = m_sourceFilePaths.size();

	char *buffer = new char[BUFFER_SIZE];
	const int pcmBufferSize = BUFFER_SIZE * 100;
	short *left = new short[pcmBufferSize];
	short *right = new short[pcmBufferSize];

	if (buffer == nullptr || left == nullptr || right == nullptr)
		throw OutOfMemoryException();

	for (m_currentFileIndex = 0; m_currentFileIndex < m_sourceFilePaths.size(); m_currentFileIndex++) {
		m_currentFileProgress = 0;
		emit progressChanged(calculateProgress());

		QFile mp3File(m_sourceFilePaths[m_currentFileIndex]);
		QFileInfo mp3FileInfo(mp3File);
		if (!mp3File.open(QFile::ReadOnly)) {
			qCritical("%s: Failed to open source MP3 file: %s", qPrintable(TAG),
					  qPrintable(m_sourceFilePaths[m_currentFileIndex]));
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}

		auto hipGlobalFlags = hip_decode_init();
		mp3data_struct mp3Config;

		WavEncoder::Config wavConfig;
		wavConfig.format = WavEncoder::PCM;
		wavConfig.sampleRate = m_settings.sampleRate;
		wavConfig.bitsPerSample = m_settings.bitsPerSameple;

		qint64 bytesRead = 0;
		qint64 samplesRead = 0;
		bool isMp3HeaderRead = false;
		do {
			bytesRead = mp3File.read(buffer, BUFFER_SIZE);
			if (bytesRead <= 0) {
				qCritical("%s: Failed to read MP3 header", qPrintable(TAG));
				m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
				emit convertionResultAdded(m_convertionResults.last());
			} else {
				samplesRead = hip_decode_headers(hipGlobalFlags, (unsigned char *) buffer, bytesRead, left, right,
												 &mp3Config);
				if (samplesRead > 0) {
					isMp3HeaderRead = true;
					wavConfig.numberOfChannels = mp3Config.stereo;
				}
			}
		} while (samplesRead == 0);
		if (!isMp3HeaderRead) {
			qCritical("%s: MP3 header not founjd", qPrintable(TAG));
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			mp3File.close();
			hip_decode_exit(hipGlobalFlags);
			continue;
		}

		//// Debug {
		QFile dbgWavFile(QDir::homePath() + QDir::separator() + "dbg.wav");
		dbgWavFile.open(QFile::ReadWrite);
		WavEncoder::Config dbgWavConfig;
		dbgWavConfig.format = WavEncoder::PCM;
		dbgWavConfig.sampleRate = mp3Config.samplerate;
		dbgWavConfig.bitsPerSample = 16;
		dbgWavConfig.numberOfChannels = 1;
		WavEncoder dbgWavEncoder(dbgWavFile, dbgWavConfig);
		dbgWavEncoder.init();
		dbgWavEncoder.encode((char *) left,
							 samplesRead * dbgWavConfig.numberOfChannels * dbgWavConfig.bitsPerSample / 8);
		//// } Debug

		QString wavFilePath = m_destDirPath + QDir::separator() + mp3FileInfo.baseName() + ".wav";
		QFile wavFile(wavFilePath);
		if (!wavFile.open(QFile::ReadWrite)) {
			qCritical("%s: Failed to open destination WAV file: %s", qPrintable(TAG), qPrintable(wavFilePath));
			hip_decode_exit(hipGlobalFlags);
			mp3File.close();
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}
		WavEncoder wavEncoder(wavFile, wavConfig);
		if (!wavEncoder.init()) {
			qCritical("%s: Failed init WAV encoder", qPrintable(TAG));
			hip_decode_exit(hipGlobalFlags);
			mp3File.close();
			wavFile.close();
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}

		SoundBufferParams sourceBufferParams = {
			.sampleRate = (quint32) mp3Config.samplerate,
			.numberOfChannels = mp3Config.stereo,
			.bitsPerSample = 16,
			.numberOfSamples = pcmBufferSize / mp3Config.stereo / 2
		};
		SoundBufferParams destBufferParams = {
			.sampleRate = wavConfig.sampleRate,
			.numberOfChannels = wavConfig.numberOfChannels,
			.bitsPerSample = wavConfig.bitsPerSample,
			.numberOfSamples = 0 // Any(will be calculated considering source buffer params in Resampler)
		};
		Resampler resampler(sourceBufferParams, destBufferParams);
		const int bufferSize = BUFFER_SIZE;
		const int maxReadSize = std::min(sourceBufferParams.numberOfSamples * sourceBufferParams.numberOfChannels * 8 /
										 sourceBufferParams.bitsPerSample, bufferSize);

		merge((qint16 *) resampler.sourceBuffer().data(), left, right, samplesRead);

		resampler.resample(samplesRead);
		quint32 bytesToEncode = resampler.destSamplesAvailable() * destBufferParams.numberOfChannels *
				destBufferParams.bitsPerSample / 8;
		if (wavEncoder.encode((char *) resampler.destBuffer().data(), bytesToEncode) < bytesToEncode) {
			qCritical("%s: Failed to encode WAV", qPrintable(TAG));
			hip_decode_exit(hipGlobalFlags);
			mp3File.close();
			wavFile.close();
			m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
			emit convertionResultAdded(m_convertionResults.last());
			continue;
		}

		qint64 totalBytesRead = 0;
		while ((bytesRead = mp3File.read(buffer, maxReadSize)) > 0) {
			samplesRead = hip_decode(hipGlobalFlags, (unsigned char *) buffer, bytesRead, left, right);
			if (samplesRead > 0) {
				dbgWavEncoder.encode((char *) left,
									 samplesRead * dbgWavConfig.numberOfChannels * dbgWavConfig.bitsPerSample / 8);

				merge((qint16 *) resampler.sourceBuffer().data(), left, right, samplesRead);

				resampler.resample(samplesRead);

				SoundBufferParams destBufferParams = resampler.destBuffer().params();
				quint32 bytesToEncode = resampler.destSamplesAvailable() * destBufferParams.numberOfChannels *
						destBufferParams.bitsPerSample / 8;
				if (wavEncoder.encode((char *) resampler.destBuffer().data(), bytesToEncode) < bytesToEncode) {
					qCritical("%s: Failed to encode WAV", qPrintable(TAG));
					hip_decode_exit(hipGlobalFlags);
					mp3File.close();
					wavFile.close();
					m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
					emit convertionResultAdded(m_convertionResults.last());
					continue;
				}
			}

			totalBytesRead += bytesRead;
			m_currentFileProgress = float(totalBytesRead) / mp3FileInfo.size();
			emit progressChanged(calculateProgress());

			if (isInterruptionRequested()) {
				hip_decode_exit(hipGlobalFlags);
				mp3File.close();
				wavFile.close();
				goto interruption_requested;
			}
		}

		dbgWavEncoder.finish();
		dbgWavFile.close();

		m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], SUCCESS);
		emit convertionResultAdded(m_convertionResults.last());

		wavEncoder.finish();
		mp3File.close();
		wavFile.close();
		hip_decode_exit(hipGlobalFlags);
	}

interruption_requested:
	delete[] buffer;
	delete[] left;
	delete[] right;
}

void Mp3ToWavConverterThread::merge(qint16 *interleavedBuffer, qint16 *leftChannelBuffer, qint16 *rightChannleBuffer,
									int numberOfSamples)
{
	for (int i = 0; i < numberOfSamples; i++) {
		interleavedBuffer[i * 2] = leftChannelBuffer[i];
		interleavedBuffer[i * 2 + 1] = rightChannleBuffer[i];
	}
}
