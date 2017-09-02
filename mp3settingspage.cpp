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

#include "mp3settingspage.h"
#include "ui_mp3settingspage.h"

Mp3SettingsPage::Mp3SettingsPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::Mp3SettingsPage),
	m_wizardViewModel(wizardViewModel)
{
	ui->setupUi(this);

	ui->bitrateComboBox->addItems(ConverterWizardViewModel::mp3BitrateNames());
	ui->bitrateComboBox->setCurrentIndex(m_wizardViewModel.mp3BitrateIndex());

	connect(ui->bitrateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onBitrateIndexChanged(int)));
}

void Mp3SettingsPage::onBitrateIndexChanged(int index)
{
	m_wizardViewModel.setMp3BitrateIndex(index);
}

Mp3SettingsPage::~Mp3SettingsPage()
{
	delete ui;
}
