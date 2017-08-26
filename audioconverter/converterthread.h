#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QThread>
#include <QStringList>

class ConverterThread : public QThread
{
	Q_OBJECT

public:
	ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, QObject *parent = 0) :
		QThread(parent),
		m_sourceFilePaths(sourceFilePaths),
		m_destDirPath(destDirPath)
	{}

signals:
	void progressChanged(float progress);

protected:
	QStringList m_sourceFilePaths;
	QString m_destDirPath;
};

#endif // CONVERTERTHREAD_H
