#ifndef CONVERTERWIZARDVIEWMODEL_H
#define CONVERTERWIZARDVIEWMODEL_H

#include <QObject>
#include <QSettings>
#include <QStringList>

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

	QStringList &sourceFilePaths() { return m_sourceFilePaths; }

	QString destDirPath() const { return m_destDirPath; }
	void setDestDirPath(QString destDirPath) { m_destDirPath = destDirPath; }

	int mp3BitrateIndex() const { return m_mp3BitrateIndex; }
	void setMp3BitrateIndex(int bitrateIndex) { m_mp3BitrateIndex = bitrateIndex; }

private:
	static const QString CONVERTION_WAY_KEY;
	static const QString MP3_BITRATE_INDEX_KEY;

	QSettings m_settings;
	ConvertionWay m_convertionWay;
	QStringList m_sourceFilePaths;
	QString m_destDirPath;
	int m_mp3BitrateIndex;
};

#endif // CONVERTERWIZARDVIEWMODEL_H
