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
