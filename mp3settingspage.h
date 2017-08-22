#ifndef MP3SETTINGSPAGE_H
#define MP3SETTINGSPAGE_H

#include <QWizardPage>

namespace Ui {
class Mp3SettingsPage;
}

class Mp3SettingsPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit Mp3SettingsPage(QWidget *parent = 0);
	~Mp3SettingsPage();

private:
	Ui::Mp3SettingsPage *ui;
};

#endif // MP3SETTINGSPAGE_H
