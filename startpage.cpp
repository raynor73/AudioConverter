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
