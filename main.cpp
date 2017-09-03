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

#ifdef PORTABLE
	QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + APPLICATION_NAME + ".ini";
	QSettings settings(filePath, QSettings::IniFormat);
#else
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope, ORGANIZATION_NAME, APPLICATION_NAME);
#endif

/*#ifndef QT_NO_TRANSLATION
	QTranslator qtTranslator;
	qDebug() << "qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath);
	if (qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
		app.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	if (appTranslator.load("myapp_" + QLocale::system().name()))
		app.installTranslator(&appTranslator);
#endif*/

	ConverterWizard wizard(settings);
	wizard.show();

	return app.exec();
}
