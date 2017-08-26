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
