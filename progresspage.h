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

	void initializePage() override;

private:
	Ui::ProgressPage *ui;
	AudioConverter &m_audioConverter;
	bool m_isListenersConnected;

	void updateWizardButtons(AudioConverter::State state);
};

#endif // PROGRESSPAGE_H
