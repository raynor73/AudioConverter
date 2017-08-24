#include "converterthread.h"
#include <cmath>
#include <lame/lame.h>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <wavdecoder.h>

const QString ConverterThread::TAG = "ConverterThread";

ConverterThread::ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, QObject *parent) :
	QThread(parent),
	m_sourceFilePaths(sourceFilePaths),
	m_destDirPath(destDirPath)
{}

void ConverterThread::run()
{
	m_totalFiles = m_sourceFilePaths.size();
	for (m_currentFileIndex = 0; m_currentFileIndex < m_sourceFilePaths.size(); m_currentFileIndex++) {
		m_currentFileProgress = 0;
		emit progressChanged(calculateProgress());

		auto lameGlobalFlags = lame_init();
		lame_set_num_channels(lameGlobalFlags, 2); // From source file
		lame_set_in_samplerate(lameGlobalFlags, 44100); // From source file
		lame_set_brate(lameGlobalFlags, 128); // From wizard
		lame_set_quality(lameGlobalFlags, 2); // Hardcoded
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
			m_currentFileProgress = float(bytesRead) / wavFileInfo.size();
			emit progressChanged(calculateProgress());
		}
		bytesToWrite = lame_encode_flush(lameGlobalFlags, mp3Buffer, mp3BufferSize);
		mp3File.write((char *) mp3Buffer, bytesToWrite);

		delete wavDecoder;
		wavFile.close();
		mp3File.close();
		lame_close(lameGlobalFlags);
	}
}

float ConverterThread::calculateProgress()
{
	if (m_totalFiles == 0)
		return 0;

	return	float(m_currentFileIndex + m_currentFileProgress) / m_totalFiles;
}
