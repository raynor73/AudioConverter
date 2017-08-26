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
