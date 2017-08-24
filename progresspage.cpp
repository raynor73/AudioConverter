#include "progresspage.h"
#include "ui_progresspage.h"

ProgressPage::ProgressPage(AudioConverter &audioConverter, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::ProgressPage),
	m_audioConverter(audioConverter)
{
	ui->setupUi(this);

	connect(&m_audioConverter, &AudioConverter::progressChanged, [this](float progress) {
		ui->progressBar->setValue(progress * 100);
	});
}

ProgressPage::~ProgressPage()
{
	delete ui;
}
