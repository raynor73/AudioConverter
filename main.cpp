#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QFileDialog>
#include <riffreader.h>
#include <wavdecoder.h>
#include <QDebug>
#include <lame/lame.h>
#include <QSettings>
#include "converterwizard.h"
#include <riffoutput.h>
#include <riffwriter.h>
#include <wavencoder.h>
#include <cmath>
#include <resampler.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

/*#ifdef PORTABLE
	QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + APPLICATION_NAME + ".ini";
	QSettings settings(filePath, QSettings::IniFormat);
#else
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
#endif

#ifndef QT_NO_TRANSLATION
	QTranslator qtTranslator;
	if (qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
		app.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	if (appTranslator.load("myapp_" + QLocale::system().name()))
		app.installTranslator(&appTranslator);
#endif

	ConverterWizard wizard(settings);
	wizard.show();*/

	/*QFile riffFile(QDir::homePath() + QDir::separator() + "some.riff");
	riffFile.open(QFile::ReadWrite);
	RiffOutput fileRiffOutput(&riffFile);

	RiffWriter riffWriter(fileRiffOutput);
	riffWriter.startChunk(RiffWriter::RIFF_CHUNCK_IDENTIFIER, "QWER");

	RiffOutput riffOutput(&riffWriter);
	RiffWriter nestedWriter(riffOutput);
	nestedWriter.startChunk("DATA");
	const char *data = "asdfghjkl";
	nestedWriter.writeData(data, qstrlen(data));
	nestedWriter.finishChunk();

	riffWriter.finishChunk();
	riffFile.close();*/

	/*QFile wavFile(QDir::homePath() + QDir::separator() + "some.wav");
	wavFile.open(QFile::ReadWrite);

	const int dataSize = 44;
	short *data = new short[dataSize];
	for (int i = 0; i < dataSize; i++) {
		float a = float(i) * 2.0f * M_PI / float(dataSize);
		data[i] = short(32000.0f * std::sin(a));
	}

	WavEncoder::Config config;
	config.format = WavEncoder::PCM;
	config.numberOfChannels = 1;
	config.sampleRate = 44100;
	config.bitsPerSample = 16;
	WavEncoder wavEncoder(wavFile, config);
	wavEncoder.init();
	for (int i = 0; i < 10000; i++)
		wavEncoder.encode((char *) data, dataSize * sizeof(short));
	wavEncoder.finish();

	delete[] data;
	wavFile.close();*/

	QFile sourceFile(QDir::homePath() + QDir::separator() + "some.wav");
	sourceFile.open(QFile::ReadOnly);
	QFile destFile(QDir::homePath() + QDir::separator() + "some8.wav");
	destFile.open(QFile::ReadWrite);

	WavDecoder wavDecoder(sourceFile);
	wavDecoder.init();
	WavFormat sourceFormat = wavDecoder.format();
	qDebug() << "Input" << sourceFormat.bitsPerSample << sourceFormat.sampleRate << sourceFormat.numberOfChannels;

	WavEncoder::Config destConfig;
	destConfig.format = WavEncoder::PCM;
	destConfig.numberOfChannels = 1;
	destConfig.sampleRate = 22050;
	destConfig.bitsPerSample = 8;
	WavEncoder wavEncoder(destFile, destConfig);
	wavEncoder.init();

	SoundBufferParams sourceBufferParams = {
		.sampleRate = sourceFormat.sampleRate,
		.numberOfChannels = sourceFormat.numberOfChannels,
		.bitsPerSample = sourceFormat.bitsPerSample,
		.numberOfSamples = 1000
	};
	SoundBufferParams destBufferParams = {
		.sampleRate = destConfig.sampleRate,
		.numberOfChannels = destConfig.numberOfChannels,
		.bitsPerSample = destConfig.bitsPerSample,
		.numberOfSamples = 1000
	};
	Resampler resampler(sourceBufferParams, destBufferParams);
	const int maxReadSize = sourceBufferParams.numberOfSamples *
			sourceBufferParams.numberOfChannels *
			8 /
			sourceBufferParams.bitsPerSample;
	int bytesRead = 0;
	while ((bytesRead = wavDecoder.decode((char *) resampler.sourceBuffer().data(), maxReadSize)) > 0) {
		resampler.resample(bytesRead / sourceFormat.numberOfChannels * 8 /sourceFormat.bitsPerSample);
		wavEncoder.encode((char *) resampler.destBuffer().data(),
						  resampler.destSamplesAvailable() * destConfig.bitsPerSample / 8 * destConfig.numberOfChannels);
	}

	wavEncoder.finish();

	sourceFile.close();
	destFile.close();

	return app.exec();
}
