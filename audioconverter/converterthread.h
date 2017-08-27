#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QThread>
#include <QStringList>

class ConverterThread : public QThread
{
	Q_OBJECT

public:
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

		QString filePath;
		ConvertionResult result;
	};

	ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, QObject *parent = 0) :
		QThread(parent),
		m_sourceFilePaths(sourceFilePaths),
		m_destDirPath(destDirPath)
	{
		qRegisterMetaType<ConvertionResultInfo>("ConvertionResultInfo");
	}

	const QList<ConvertionResultInfo> &convertionResults() const { return m_convertionResults; }

signals:
	void progressChanged(float progress);
	void convertionResultAdded(ConvertionResultInfo convertionResult);

protected:
	QStringList m_sourceFilePaths;
	QString m_destDirPath;
	QList<ConvertionResultInfo> m_convertionResults;
};

#endif // CONVERTERTHREAD_H
