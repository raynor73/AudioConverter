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
			return;
		}

		QFile wavFile(m_sourceFilePaths[m_currentFileIndex]);
		QFileInfo wavFileInfo(wavFile);
		wavFile.open(QFile::ReadOnly);
		WavDecoder *wavDecoder = new WavDecoder(wavFile);
		wavDecoder->init();
		lame_set_num_channels(lameGlobalFlags, wavDecoder->format().numberOfChannels);
		lame_set_in_samplerate(lameGlobalFlags, wavDecoder->format().sampleRate);
		auto mp3BufferSize = int(std::ceil(1.25 * BUFFER_SIZE / wavDecoder->format().dataBlockSize + 7200));
		auto mp3Buffer = new unsigned char[mp3BufferSize];

		QFile mp3File(m_destDirPath + QDir::separator() + wavFileInfo.baseName() + ".mp3");
		mp3File.open(QFile::WriteOnly);
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

			if (isInterruptionRequested())
				goto clean_and_exit;
		}
		bytesToWrite = lame_encode_flush(lameGlobalFlags, mp3Buffer, mp3BufferSize);
		mp3File.write((char *) mp3Buffer, bytesToWrite);

clean_and_exit:
		delete wavDecoder;
		wavFile.close();
		mp3File.close();
		lame_close(lameGlobalFlags);
	}
}

float WavToMp3ConverterThread::calculateProgress()
{
	if (m_totalFiles == 0)
		return 0;

	return	float(m_currentFileIndex + m_currentFileProgress) / m_totalFiles;
}
