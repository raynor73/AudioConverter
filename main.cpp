#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
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

	return app.exec();
}
