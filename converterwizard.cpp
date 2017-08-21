#include "converterwizard.h"
#include <QCoreApplication>
#include "startpage.h"
#include "filesselectionpage.h"
#include "wavsettingspage.h"

const QString ConverterWizard::WIZARD_WINDOW_POSITION_KEY = "wizard/position";

ConverterWizard::ConverterWizard(QWidget *parent) : QWizard(parent)
{
	setPage(Page_Start, new StartPage(m_viewModel));
	setPage(Page_FilesSelection, new FilesSelectionPage(m_viewModel));
	setPage(Page_WavSetings, new WavSettingsPage);

#ifndef Q_OS_MAC
	setWizardStyle(ModernStyle);
#endif

	setWindowTitle(tr("Converter Wizard"));

	readSettings();

	connect(this, &ConverterWizard::finished, [this]() {
		writeSettings();
	});
}

int ConverterWizard::nextId() const
{
	switch (currentId())
	{
	case Page_Start:
		return Page_FilesSelection;

	case Page_FilesSelection:
		return m_viewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3 ? Page_Mp3Settings : Page_WavSetings;

	default:
		return -1;
	}
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
