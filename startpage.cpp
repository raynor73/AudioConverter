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

#include "startpage.h"
#include "ui_startpage.h"
#include <QMetaEnum>

StartPage::StartPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent) :
	QWizardPage(parent),
	m_ui(new Ui::StartPage),
	m_wizardViewModel(wizardViewModel)
{
	m_ui->setupUi(this);

	m_ui->wavToMp3RadioButton->setChecked(false);
	m_ui->mp3ToWavRadioButton->setChecked(false);

	if (m_wizardViewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3)
		m_ui->wavToMp3RadioButton->setChecked(true);
	else
		m_ui->mp3ToWavRadioButton->setChecked(true);

	connect(m_ui->wavToMp3RadioButton, &QRadioButton::toggled, [this](bool checked) {
		if (checked)
			m_wizardViewModel.setConvertionWay(ConverterWizardViewModel::WAV_TO_MP3);
		else
			m_wizardViewModel.setConvertionWay(ConverterWizardViewModel::MP3_TO_WAV);
	});
}

StartPage::~StartPage()
{
	delete m_ui;
}
