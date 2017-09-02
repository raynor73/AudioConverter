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

#ifndef PROGRESSPAGE_H
#define PROGRESSPAGE_H

#include <QWizardPage>
#include <audioconverter.h>

namespace Ui {
class ProgressPage;
}

class ProgressPage : public QWizardPage
{
	Q_OBJECT

public:
	ProgressPage(AudioConverter &audioConverter, QWidget *parent = 0);
	~ProgressPage();

	void initializePage() override;

private:
	Ui::ProgressPage *ui;
	AudioConverter &m_audioConverter;
	bool m_isListenersConnected;

	void updateWizardButtons(AudioConverter::State state);
	void resetTable();
};

#endif // PROGRESSPAGE_H
