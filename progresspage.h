#ifndef PROGRESSPAGE_H
#define PROGRESSPAGE_H

#include <QWizardPage>
#include <audioconverter.h>

namespace Ui {
class ProgressPage;
}

class ProgressPage : public QWizardPage
{
	Q_OBJECT

public:
	ProgressPage(AudioConverter &audioConverter, QWidget *parent = 0);
	~ProgressPage();

private:
	Ui::ProgressPage *ui;
	AudioConverter &m_audioConverter;
};

#endif // PROGRESSPAGE_H
