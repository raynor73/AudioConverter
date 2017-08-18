#include "converterwizard.h"
#include <QCoreApplication>
#include "startpage.h"

ConverterWizard::ConverterWizard(QWidget *parent) : QWizard(parent)
{
	QCoreApplication::setOrganizationName("Lapin Soft");
	QCoreApplication::setApplicationName("Audio Converter");

	addPage(new StartPage);

#ifndef Q_OS_MAC
	setWizardStyle(ModernStyle);
#endif

	setWindowTitle(tr("Converter Wizard"));
}
