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

#ifndef MP3SETTINGSPAGE_H
#define MP3SETTINGSPAGE_H

#include <QWizardPage>
#include <QMap>
#include "converterwizardviewmodel.h"

namespace Ui {
class Mp3SettingsPage;
}

class Mp3SettingsPage : public QWizardPage
{
	Q_OBJECT

public:
	Mp3SettingsPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent = 0);
	~Mp3SettingsPage();

private slots:
	void onBitrateIndexChanged(int index);

private:
	Ui::Mp3SettingsPage *ui;
	ConverterWizardViewModel &m_wizardViewModel;
};

#endif // MP3SETTINGSPAGE_H
