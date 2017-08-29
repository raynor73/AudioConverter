#include "riffoutput.h"
#include "riffwriter.h"

RiffOutput::RiffOutput(QIODevice *ioDevice, QObject *parent) :
	QObject(parent),
	m_ioDevice(ioDevice),
	m_riffWriter(nullptr)
{
	if (m_ioDevice->isSequential())
		throw DeviceIsSequentialException();
}

RiffOutput::RiffOutput(RiffWriter *riffWriter, QObject *parent) :
	QObject(parent),
	m_ioDevice(nullptr),
	m_riffWriter(riffWriter)
{}

qint64 RiffOutput::write(const char *data, qint64 maxSize)
{
	if (m_ioDevice != nullptr)
		return m_ioDevice->write(data, maxSize);
	else
		return m_riffWriter->writeData(data, maxSize);
}

bool RiffOutput::seek(qint64 pos)
{
	if (m_ioDevice != nullptr)
		return m_ioDevice->seek(pos);
	else
		return m_riffWriter->seek(pos);
}

qint64 RiffOutput::pos() const
{
	if (m_ioDevice != nullptr)
		return m_ioDevice->pos();
	else
		return m_riffWriter->pos();
}
