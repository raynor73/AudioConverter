#include <QApplication>
#include "converterwizard.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#ifndef QT_NO_TRANSLATION
	QString translatorFileName = QLatin1String("qt_");
	translatorFileName += QLocale::system().name();
	QTranslator *translator = new QTranslator(&app);
	if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
		app.installTranslator(translator);
#endif

	/*QTranslator qtTranslator;
		qtTranslator.load("qt_" + QLocale::system().name(),
				QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		app.installTranslator(&qtTranslator);

		QTranslator myappTranslator;
		myappTranslator.load("myapp_" + QLocale::system().name());
		app.installTranslator(&myappTranslator);*/

	ConverterWizard wizard;
	wizard.show();

	return a.exec();
}
