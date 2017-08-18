#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWizardPage>
#include <QSettings>

namespace Ui {
class StartPage;
}

class StartPage : public QWizardPage
{
	Q_OBJECT

public:
	explicit StartPage(QWidget *parent = 0);
	~StartPage();

private:
	QSettings m_settings;
	Ui::StartPage *m_ui;
};

#endif // STARTPAGE_H
