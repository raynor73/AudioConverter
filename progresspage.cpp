#include "progresspage.h"
#include "ui_progresspage.h"
#include <QAbstractButton>
#include <QMetaEnum>
#include <QDebug>

ProgressPage::ProgressPage(AudioConverter &audioConverter, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::ProgressPage),
	m_audioConverter(audioConverter),
	m_isListenersConnected(false)
{
	ui->setupUi(this);

	resetTable();

	connect(&m_audioConverter, &AudioConverter::progressChanged, [this](float progress) {
		ui->progressBar->setValue(progress * 100);
	});

	connect(&m_audioConverter, &AudioConverter::stateChanged, [this](AudioConverter::State state) {
		if (state == AudioConverter::WORKING) {
			ui->progressBar->setVisible(true);

			resetTable();
		} else {
			ui->progressBar->setVisible(false);
		}
	});

	connect(&m_audioConverter, &AudioConverter::convertionResultAdded,
			[this](AudioConverter::ConvertionResultInfo result) {

		QTableWidgetItem *pathItem = new QTableWidgetItem(result.filePath);
		QString resultString = QMetaEnum::fromType<AudioConverter::ConvertionResult>().valueToKey(result.result);
		QTableWidgetItem *resultItem = new QTableWidgetItem(resultString);

		if (result.result == AudioConverter::SUCCESS) {
			pathItem->setBackgroundColor(QColor::fromRgb(0xb6, 0xff, 0xb6));
			resultItem->setBackgroundColor(QColor::fromRgb(0xb6, 0xff, 0xb6));
		} else {
			pathItem->setBackgroundColor(QColor::fromRgb(0xff, 0xb6, 0xb6));
			resultItem->setBackgroundColor(QColor::fromRgb(0xff, 0xb6, 0xb6));
		}

		int row = ui->tableWidget->rowCount();
		ui->tableWidget->setRowCount(row + 1);
		ui->tableWidget->setItem(row, 0, pathItem);
		ui->tableWidget->setItem(row, 1, resultItem);
	});
}

ProgressPage::~ProgressPage()
{
	delete ui;
}

void ProgressPage::resetTable()
{
	ui->tableWidget->clear();
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setHorizontalHeaderLabels({ tr("Path"), tr("Result") });

	ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
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
