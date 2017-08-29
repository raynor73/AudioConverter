#ifndef RIFFOUTPUT_H
#define RIFFOUTPUT_H

#include <QObject>
#include <QIODevice>
#include <QException>

class RiffWriter;

class RiffOutput : public QObject
{
	Q_OBJECT
public:
	class DeviceIsSequentialException : QException {};

	RiffOutput(QIODevice *ioDevice, QObject *parent = 0);
	RiffOutput(RiffWriter *riffWriter, QObject *parent = 0);

	qint64 write(const char *data, qint64 maxSize);
	bool seek(qint64 pos);
	qint64 pos() const;

private:
	QIODevice *m_ioDevice;
	RiffWriter *m_riffWriter;
};

#endif // RIFFOUTPUT_H
