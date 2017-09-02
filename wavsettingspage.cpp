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

#include "wavsettingspage.h"
#include "ui_wavsettingspage.h"

WavSettingsPage::WavSettingsPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::WavSettingsPage),
	m_wizardViewModel(wizardViewModel)
{
	ui->setupUi(this);

	ui->sampleRateComboBox->addItems(ConverterWizardViewModel::wavSampleRateNames());
	ui->sampleRateComboBox->setCurrentIndex(m_wizardViewModel.wavSampleRateIndex());
	ui->bitsPerSampleComboBox->addItems(ConverterWizardViewModel::wavBitsPerSampleNames());
	ui->bitsPerSampleComboBox->setCurrentIndex(m_wizardViewModel.wavBitsPerSampleIndex());

	connect(ui->sampleRateComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
			[this](int index) {
		m_wizardViewModel.setWavSampleRateIndex(index);
	});
	connect(ui->bitsPerSampleComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
			[this](int index) {
		m_wizardViewModel.setWavBitsPerSampleIndex(index);
	});
}

WavSettingsPage::~WavSettingsPage()
{
	delete ui;
}
