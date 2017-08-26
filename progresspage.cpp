#include "progresspage.h"
#include "ui_progresspage.h"
#include <QAbstractButton>
#include <QDebug>

ProgressPage::ProgressPage(AudioConverter &audioConverter, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::ProgressPage),
	m_audioConverter(audioConverter),
	m_isListenersConnected(false)
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

void ProgressPage::initializePage()
{
	if (!m_isListenersConnected) {
		m_isListenersConnected = true;

		connect(wizard(), &QWizard::rejected, [this]() {
			if (m_audioConverter.state() == AudioConverter::WORKING)
				m_audioConverter.cancel();
		});

		connect(&m_audioConverter, &AudioConverter::stateChanged, [this](AudioConverter::State state) {
			updateWizardButtons(state);
		});
	}

	updateWizardButtons(m_audioConverter.state());
}

void ProgressPage::updateWizardButtons(AudioConverter::State state)
{
	if (state == AudioConverter::IDLE) {
		wizard()->button(QWizard::NextButton)->setEnabled(true);
		wizard()->button(QWizard::BackButton)->setEnabled(true);
		wizard()->button(QWizard::FinishButton)->setEnabled(true);
	} else {
		wizard()->button(QWizard::NextButton)->setEnabled(false);
		wizard()->button(QWizard::BackButton)->setEnabled(false);
		wizard()->button(QWizard::FinishButton)->setEnabled(false);
	}
}
