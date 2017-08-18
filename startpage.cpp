#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent) :
	QWizardPage(parent),
	m_ui(new Ui::StartPage)
{
	m_ui->setupUi(this);

	if (m_settings.value())
	//ui->
}

StartPage::~StartPage()
{
	delete m_ui;
}
