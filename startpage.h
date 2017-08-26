#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWizardPage>
#include <QSettings>
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
