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

#ifndef CONVERTERWIZARD_H
#define CONVERTERWIZARD_H


#include <QWizard>
#include <QSettings>
#include <QCloseEvent>
#include "converterwizardviewmodel.h"
#include <audioconverter.h>

class ConverterWizard : public QWizard
{
	Q_OBJECT

public:
	enum { Page_Start, Page_FilesSelection, Page_WavSetings, Page_Mp3Settings, Page_Progress };

	ConverterWizard(QSettings &settings, QWidget *parent = nullptr);

	int nextId() const override;

protected:
	void closeEvent(QCloseEvent *closeEvent) override;

private:
	static const QString WIZARD_WINDOW_POSITION_KEY;

	QSettings &m_settings;
	ConverterWizardViewModel m_viewModel;
	AudioConverter m_audioConverter;

	void writeSettings();
	void readSettings();
};

#endif // CONVERTERWIZARD_H
