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

#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWizardPage>
#include "converterwizardviewmodel.h"

namespace Ui {
class StartPage;
}

class StartPage : public QWizardPage
{
	Q_OBJECT

public:
	StartPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent = 0);
	~StartPage();

private:
	Ui::StartPage *m_ui;
	ConverterWizardViewModel &m_wizardViewModel;
};

#endif // STARTPAGE_H
