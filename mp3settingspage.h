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
	QList <QString> m_bitrates = {
		"32", "40", "48", "56", "64", "80", "96", "112", "128", "160", "192", "224", "256", "320"
	};
	QMap<QString, int> m_bitratesMap = {
		{"32", 32},
		{"40", 40},
		{"48", 48},
		{"56", 56},
		{"64", 64},
		{"80", 80},
		{"96", 96},
		{"112", 112},
		{"128", 128},
		{"160", 160},
		{"192", 192},
		{"224", 224},
		{"256", 256},
		{"320", 320}
	};
	ConverterWizardViewModel &m_wizardViewModel;
};

#endif // MP3SETTINGSPAGE_H
