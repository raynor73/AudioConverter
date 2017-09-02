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

#include "progresspage.h"
#include "ui_progresspage.h"
#include <QAbstractButton>
#include <QMetaEnum>
#include <QFileInfo>
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

		QTableWidgetItem *pathItem = new QTableWidgetItem(QFileInfo (result.filePath).fileName());
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
		wizard()->button(QWizard::CancelButton)->setVisible(false);
	} else {
		wizard()->button(QWizard::NextButton)->setEnabled(false);
		wizard()->button(QWizard::BackButton)->setEnabled(false);
		wizard()->button(QWizard::FinishButton)->setEnabled(false);
		wizard()->button(QWizard::CancelButton)->setVisible(true);
	}
}
