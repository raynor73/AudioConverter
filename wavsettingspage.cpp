#include "wavsettingspage.h"
#include "ui_wavsettingspage.h"

WavSettingsPage::WavSettingsPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::WavSettingsPage)
{
	ui->setupUi(this);
}

WavSettingsPage::~WavSettingsPage()
{
	delete ui;
}
