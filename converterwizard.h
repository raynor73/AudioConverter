#ifndef CONVERTERWIZARD_H
#define CONVERTERWIZARD_H


#include <QWizard>
#include <QSettings>
#include <QCloseEvent>
#include "converterwizardviewmodel.h"

class ConverterWizard : public QWizard
{
	Q_OBJECT

public:
	ConverterWizard(QWidget *parent = nullptr);

private:
	static const QString WIZARD_WINDOW_POSITION_KEY;

	QSettings m_settings;
	ConverterWizardViewModel m_viewModel;

	void writeSettings();
	void readSettings();
};

#endif // CONVERTERWIZARD_H
