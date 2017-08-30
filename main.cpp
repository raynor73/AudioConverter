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

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#ifdef PORTABLE
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
	wizard.show();

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

	return app.exec();
}
