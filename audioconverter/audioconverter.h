#ifndef AUDIOCONVERTER_H
#define AUDIOCONVERTER_H

#include <QObject>
#include <QStringList>
#include <QMetaType>
#include "converterthread.h"

class AudioConverter : public QObject
{
	Q_OBJECT

public:
	enum ConvertionWay { WAV_TO_MP3, MP3_TO_WAV };
	Q_ENUM(ConvertionWay)

	struct Settings
	{
		ConvertionWay convertionWay;
		int mp3Bitrate;
	};

	enum ConvertionResult { SUCCESS, FAILURE };
	Q_ENUM(ConvertionResult)

	struct ConvertionResultInfo
	{
		ConvertionResultInfo() : result(FAILURE) {}

		ConvertionResultInfo(QString filePath, ConvertionResult result)
		{
			this->filePath = filePath;
			this->result = result;
		}

		ConvertionResultInfo(const ConverterThread::ConvertionResultInfo &other)
		{
			filePath = other.filePath;

			switch (other.result) {
			case ConverterThread::SUCCESS:
				result = SUCCESS;
				break;

			case ConverterThread::FAILURE:
				result = FAILURE;
				break;
			}
		}

		QString filePath;
		ConvertionResult result;
	};

	explicit AudioConverter(QObject *parent = 0);
	~AudioConverter();

	enum State { IDLE, WORKING };
	Q_ENUM(State)

	State state() const { return m_state; }

	void convert(const QStringList &sourceFilePaths, const QString &destDirPath, Settings settings);
	void cancel();
	float progress() const { return m_progress; }
	const QList<ConvertionResultInfo> &convertionResults() const { return m_convertionResults; }

signals:
	void stateChanged(State state);
	void progressChanged(float progress);
	void convertionResultAdded(ConvertionResultInfo convertionResult);

private:
	static const QString TAG;

	State m_state;
	float m_progress;
	ConverterThread *m_converterThread;
	QList<ConvertionResultInfo> m_convertionResults;

	void changeState(State newState);
};

#endif // AUDIOCONVERTER_H
