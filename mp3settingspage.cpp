#include "mp3settingspage.h"
#include "ui_mp3settingspage.h"

Mp3SettingsPage::Mp3SettingsPage(QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::Mp3SettingsPage)
{
	ui->setupUi(this);
}

Mp3SettingsPage::~Mp3SettingsPage()
{
	delete ui;
}
