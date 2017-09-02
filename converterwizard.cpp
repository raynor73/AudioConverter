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

#include "converterwizard.h"
#include <QCoreApplication>
#include "startpage.h"
#include "filesselectionpage.h"
#include "wavsettingspage.h"
#include "mp3settingspage.h"
#include "progresspage.h"

const QString ConverterWizard::WIZARD_WINDOW_POSITION_KEY = "wizard/position";

ConverterWizard::ConverterWizard(QSettings &settings, QWidget *parent) :
	QWizard(parent),
	m_settings(settings),
	m_viewModel(settings)
{
	setPage(Page_Start, new StartPage(m_viewModel));
	setPage(Page_FilesSelection, new FilesSelectionPage(m_viewModel));
	setPage(Page_WavSetings, new WavSettingsPage(m_viewModel));
	setPage(Page_Mp3Settings, new Mp3SettingsPage(m_viewModel));
	setPage(Page_Progress, new ProgressPage(m_audioConverter));

#ifndef Q_OS_MAC
	setWizardStyle(ModernStyle);
#endif

	setWindowTitle(tr("Converter Wizard"));

	readSettings();

	connect(this, &ConverterWizard::finished, [this]() {
		writeSettings();
	});

	connect(this, &ConverterWizard::currentIdChanged, [this](int currentId) {
		if (currentId == Page_Progress) {
			AudioConverter::Settings settings;
			if (m_viewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3) {
				settings.convertionWay = AudioConverter::WAV_TO_MP3;
				settings.mp3Bitrate = ConverterWizardViewModel::mp3BitrateValues()[m_viewModel.mp3BitrateIndex()];
			} else {
				settings.convertionWay = AudioConverter::MP3_TO_WAV;
				settings.wavSampleRate =
						ConverterWizardViewModel::wavSampleRateValues()[m_viewModel.wavSampleRateIndex()];
				settings.wavBitsPerSample =
						ConverterWizardViewModel::wavBitsPerSampleValues()[m_viewModel.wavBitsPerSampleIndex()];
			}
			m_audioConverter.convert(m_viewModel.sourceFilePaths(), m_viewModel.destDirPath(), settings);
		}
	});
}

void ConverterWizard::closeEvent(QCloseEvent *closeEvent)
{
	if (m_audioConverter.state() == AudioConverter::WORKING)
		m_audioConverter.cancel();

	closeEvent->accept();
}

int ConverterWizard::nextId() const
{
	switch (currentId())
	{
	case Page_Start:
		return Page_FilesSelection;

	case Page_FilesSelection:
		return m_viewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3 ? Page_Mp3Settings : Page_WavSetings;

	case Page_WavSetings:
	case Page_Mp3Settings:
		return Page_Progress;

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
