#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QThread>
#include <QStringList>

class ConverterThread : public QThread
{
	Q_OBJECT

public:
	ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, QObject *parent = 0);

signals:
	void progressChanged(float progress);

protected:
	void run() override;

private:
	static const QString TAG;
	static const int BUFFER_SIZE = 102400;

	QStringList m_sourceFilePaths;
	QString m_destDirPath;

	int m_totalFiles;
	int m_currentFileIndex;
	float m_currentFileProgress;

	float calculateProgress();
};

#endif // CONVERTERTHREAD_H
