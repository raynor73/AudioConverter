#ifndef CONVERTERWIZARD_H
#define CONVERTERWIZARD_H


#include <QWizard>
#include <QSettings>
#include <QCloseEvent>
#include "converterwizardviewmodel.h"
#include <audioconverter.h>

class ConverterWizard : public QWizard
{
	Q_OBJECT

public:
	enum { Page_Start, Page_FilesSelection, Page_WavSetings, Page_Mp3Settings, Page_Progress };

	ConverterWizard(QWidget *parent = nullptr);

	int nextId() const override;

protected:
	void closeEvent(QCloseEvent *closeEvent) override;

private:
	static const QString WIZARD_WINDOW_POSITION_KEY;

	QSettings m_settings;
	ConverterWizardViewModel m_viewModel;
	AudioConverter m_audioConverter;

	void writeSettings();
	void readSettings();
};

#endif // CONVERTERWIZARD_H
