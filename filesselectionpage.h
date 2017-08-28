#ifndef FILESSELECTIONPAGE_H
#define FILESSELECTIONPAGE_H

#include <QWizardPage>
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

	bool isComplete() const override;

private:
	Ui::FilesSelectionPage *ui;
	ConverterWizardViewModel &m_wizardViewModel;
};

#endif // FILESSELECTIONPAGE_H
