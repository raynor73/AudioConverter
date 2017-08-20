#ifndef FILESSELECTIONPAGE_H
#define FILESSELECTIONPAGE_H

#include <QWizardPage>
#include <QSettings>
#include "converterwizardviewmodel.h"

namespace Ui {
class FilesSelectionPage;
}

class FilesSelectionPage : public QWizardPage
{
	Q_OBJECT

public:
	FilesSelectionPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent = 0);
	virtual ~FilesSelectionPage();

private:
	static const QString PREV_SOURCE_DIR_KEY;
	static const QString PREV_DEST_DIR_KEY;

	Ui::FilesSelectionPage *ui;
	ConverterWizardViewModel &m_wizardViewModel;
	QSettings m_settings;
	QString m_sourceDir;
	QString m_destDirPath;
};

#endif // FILESSELECTIONPAGE_H
