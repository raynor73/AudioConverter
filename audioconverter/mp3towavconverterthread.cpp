#include "mp3towavconverterthread.h"
#include <lame/lame.h>
#include <wavencoder.h>
#include <QFile>
#include <QFileInfo>
#include <QDir>

const QString Mp3ToWavConverterThread::TAG = "Mp3ToWavConverterThread";

Mp3ToWavConverterThread::Mp3ToWavConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath,
												 Settings settings, QObject *parent) :
	ConverterThread(sourceFilePaths, destDirPath, parent),
	m_settings(settings)
{}

void Mp3ToWavConverterThread::run()
{
	m_totalFiles = m_sourceFilePaths.size();
	for (m_currentFileIndex = 0; m_currentFileIndex < m_sourceFilePaths.size(); m_currentFileIndex++) {
		m_currentFileProgress = 0;
		emit progressChanged(calculateProgress());

		/*m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], FAILURE);
		emit convertionResultAdded(m_convertionResults.last());*/

		WavEncoder::Config config;
		config.format = WavEncoder::PCM;

		config.numberOfChannels = 1;
		config.sampleRate = 44100;
		config.bitsPerSample = 16;

		/*WavEncoder wavEncoder(wavFile, config);
		wavEncoder.init();
		for (int i = 0; i < 10000; i++)
			wavEncoder.encode((char *) data, dataSize);
		wavEncoder.finish();*/


		QFile mp3File(m_sourceFilePaths[m_currentFileIndex]);
		QFileInfo mp3FileInfo(mp3File);
		mp3File.open(QFile::ReadOnly);

		auto hipGlobalFlags = hip_decode_init();



		hip_decode_exit(hipGlobalFlags);

		/*auto lameGlobalFlags = lame_init();
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
		wavFile.open(QFile::ReadOnly);
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
				goto interruption_requested;
		}
		bytesToWrite = lame_encode_flush(lameGlobalFlags, mp3Buffer, mp3BufferSize);
		mp3File.write((char *) mp3Buffer, bytesToWrite);

		m_convertionResults += ConvertionResultInfo(m_sourceFilePaths[m_currentFileIndex], SUCCESS);
		emit convertionResultAdded(m_convertionResults.last());

interruption_requested:
		delete wavDecoder;
		mp3File.close();
		wavFile.close();
		lame_close(lameGlobalFlags);*/
	}
}
