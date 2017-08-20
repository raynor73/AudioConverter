#ifndef WAVSETTINGSPAGE_H
#define WAVSETTINGSPAGE_H

#include <QWizardPage>

namespace Ui {
class WavSettingsPage;
}

class WavSettingsPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit WavSettingsPage(QWidget *parent = 0);
	~WavSettingsPage();

private:
	Ui::WavSettingsPage *ui;
};

#endif // WAVSETTINGSPAGE_H
