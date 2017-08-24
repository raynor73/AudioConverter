#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QFileDialog>
#include <riffreader.h>
#include <wavdecoder.h>
#include <QDebug>
#include <lame/lame.h>
#include "converterwizard.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("Lapin Soft");
	QCoreApplication::setApplicationName("Audio Converter");

#ifndef QT_NO_TRANSLATION
	QTranslator qtTranslator;
	if (qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
		app.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	if (appTranslator.load("myapp_" + QLocale::system().name()))
		app.installTranslator(&appTranslator);
#endif

	ConverterWizard wizard;
	wizard.show();

	/*QString path = QFileDialog::getOpenFileName(NULL, "Pick WAV file", QDir::homePath(), "WAV files (*.wav)");
	QFile wavFile(path);
	wavFile.open(QFile::ReadOnly);
	RiffReader riffReader(wavFile);
	while (riffReader.nextChunk() == RiffReader::OK) {
		qDebug() << "Found chunk with identifier:" << riffReader.chunkHeader().identifier();
	}
	wavFile.close();*/

	/*QString path = QFileDialog::getOpenFileName(NULL, "Pick WAV file", QDir::homePath(), "WAV files (*.wav)");
	QFile wavFile(path);
	wavFile.open(QFile::ReadOnly);
	WavDecoder wavDecoder(wavFile);
	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	if (wavDecoder.init()) {
		int readBytes = 0;
		int total = 0;
		while ((readBytes = wavDecoder.decode(buffer, BUFFER_SIZE)) > 0) {
			qDebug() << "Read bytes" << readBytes;
			total += readBytes;
		}
		qDebug() << "Total" << total;
	}
	wavFile.close();*/

	return app.exec();
}
