#include "converterwizard.h"
#include <QCoreApplication>
#include "startpage.h"
#include "filesselectionpage.h"

const QString ConverterWizard::WIZARD_WINDOW_POSITION_KEY = "wizard/position";

ConverterWizard::ConverterWizard(QWidget *parent) : QWizard(parent)
{
	addPage(new StartPage(m_viewModel));
	addPage(new FilesSelectionPage(m_viewModel));

#ifndef Q_OS_MAC
	setWizardStyle(ModernStyle);
#endif

	setWindowTitle(tr("Converter Wizard"));

	readSettings();

	connect(this, &ConverterWizard::finished, [this]() {
		writeSettings();
	});
}

void ConverterWizard::writeSettings()
{
	m_settings.setValue(WIZARD_WINDOW_POSITION_KEY, pos());
}

void ConverterWizard::readSettings()
{
	if (m_settings.contains(WIZARD_WINDOW_POSITION_KEY)) {
		move(m_settings.value(WIZARD_WINDOW_POSITION_KEY).toPoint());
	}
}
