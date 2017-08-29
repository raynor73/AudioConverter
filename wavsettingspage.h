#ifndef WAVSETTINGSPAGE_H
#define WAVSETTINGSPAGE_H

#include <QWizardPage>
#include "converterwizardviewmodel.h"

namespace Ui {
class WavSettingsPage;
}

class WavSettingsPage : public QWizardPage
{
	Q_OBJECT

public:
	WavSettingsPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent = 0);
	~WavSettingsPage();

private:
	Ui::WavSettingsPage *ui;

	ConverterWizardViewModel &m_wizardViewModel;
};

#endif // WAVSETTINGSPAGE_H
