#ifndef CONVERTERWIZARDVIEWMODEL_H
#define CONVERTERWIZARDVIEWMODEL_H

#include <QObject>
#include <QSettings>

class ConverterWizardViewModel : public QObject
{
	Q_OBJECT

public:
	enum ConvertionWay { WAV_TO_MP3, MP3_TO_WAV };
	Q_ENUM(ConvertionWay)

	explicit ConverterWizardViewModel(QObject *parent = 0);
	virtual ~ConverterWizardViewModel();

	ConvertionWay convertionWay() const { return m_convertionWay; }
	void setConvertionWay(ConvertionWay convertionWay) { m_convertionWay = convertionWay; }

private:
	static const QString CONVERTION_WAY_KEY;

	QSettings m_settings;
	ConvertionWay m_convertionWay;
};

#endif // CONVERTERWIZARDVIEWMODEL_H
