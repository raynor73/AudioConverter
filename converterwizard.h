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
	enum { Page_Start, Page_FilesSelection, Page_WavSetings, Page_Mp3Settings };

	ConverterWizard(QWidget *parent = nullptr);

	int nextId() const override;

private:
	static const QString WIZARD_WINDOW_POSITION_KEY;

	QSettings m_settings;
	ConverterWizardViewModel m_viewModel;

	void writeSettings();
	void readSettings();
};

#endif // CONVERTERWIZARD_H
