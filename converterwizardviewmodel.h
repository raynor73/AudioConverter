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

	ConverterWizardViewModel(QSettings &settings, QObject *parent = 0);
	virtual ~ConverterWizardViewModel();

	ConvertionWay convertionWay() const { return m_convertionWay; }
	void setConvertionWay(ConvertionWay convertionWay) { m_convertionWay = convertionWay; }

	QStringList &sourceFilePaths() { return m_sourceFilePaths; }

	QString sourceDirPath() const { return m_sourceDirPath; }
	void setSourceDirPath(const QString &sourceDirPath) { m_sourceDirPath = sourceDirPath; }

	QString destDirPath() const { return m_destDirPath; }
	void setDestDirPath(QString destDirPath) { m_destDirPath = destDirPath; }

	int mp3BitrateIndex() const { return m_mp3BitrateIndex; }
	void setMp3BitrateIndex(int bitrateIndex) { m_mp3BitrateIndex = bitrateIndex; }

	int wavSampleRateIndex() const { return m_wavSampleRateIndex; }
	void setWavSampleRateIndex(int sampleRateIndex) { m_wavSampleRateIndex = sampleRateIndex; }

	int wavBitsPerSampleIndex() const { return m_wavBitsPerSampleIndex; }
	void setWavBitsPerSampleIndex(int bitsPerSampleIndex) { m_wavBitsPerSampleIndex = bitsPerSampleIndex; }

	static QStringList mp3BitrateNames() { return m_mp3BitrateNames; }
	static QList<int> mp3BitrateValues() { return m_mp3BitrateValues; }
	static QStringList wavSampleRateNames() { return m_wavSampleRateNames; }
	static QList<int> wavSampleRateValues() { return m_wavSampleRateValues; }
	static QStringList wavBitsPerSampleNames() { return m_wavBitsPerSampleNames; }
	static QList<int> wavBitsPerSampleValues() { return m_wavBitsPerSampleValues; }

private:
	static const QString CONVERTION_WAY_KEY;
	static const QString MP3_BITRATE_INDEX_KEY;
	static const QString SOURCE_DIR_PATH_KEY;
	static const QString DEST_DIR_PATH_KEY;
	static const QString WAV_SAMPLE_RATE_INDEX_KEY;
	static const QString WAV_BITS_PER_SAMPLE_INDEX_KEY;

	static QList<QString> m_mp3BitrateNames;
	static QList<int> m_mp3BitrateValues;
	static QStringList m_wavSampleRateNames;
	static QList<int> m_wavSampleRateValues;
	static QStringList m_wavBitsPerSampleNames;
	static QList<int> m_wavBitsPerSampleValues;

	QSettings &m_settings;
	ConvertionWay m_convertionWay;
	QStringList m_sourceFilePaths;
	QString m_sourceDirPath;
	QString m_destDirPath;
	int m_mp3BitrateIndex;
	int m_wavSampleRateIndex;
	int m_wavBitsPerSampleIndex;
};

#endif // CONVERTERWIZARDVIEWMODEL_H
