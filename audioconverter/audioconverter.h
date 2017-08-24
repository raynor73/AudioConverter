#ifndef AUDIOCONVERTER_H
#define AUDIOCONVERTER_H

#include <QObject>
#include <QStringList>
#include "converterthread.h"

class AudioConverter : public QObject
{
	Q_OBJECT

public:
	explicit AudioConverter(QObject *parent = 0);
	~AudioConverter();

	enum State { IDLE, WORKING };
	Q_ENUM(State)

	State state() const { return m_state; }

	void convert(const QStringList &sourceFilePaths, const QString &destDirPath);
	float progress() const { return m_progress; }

signals:
	void stateChanged(State state);
	void progressChanged(float progress);

private:
	static const QString TAG;

	State m_state;
	float m_progress;
	ConverterThread *m_converterThread;

	void changeState(State newState);
	void destroyThreadIfRequired();
};

#endif // AUDIOCONVERTER_H
