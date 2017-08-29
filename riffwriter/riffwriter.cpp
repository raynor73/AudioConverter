#include "riffwriter.h"
#include <QMetaEnum>
#include "riffoutput.h"

const QString RiffWriter::TAG = "TAG";
const QString RiffWriter::RIFF_CHUNCK_IDENTIFIER = "RIFF";
const QString RiffWriter::LIST_CHUNK_IDENTIFIER = "LIST";

RiffWriter::RiffWriter(RiffOutput &riffOutput, QObject *parent) :
	QObject(parent),
	m_state(IDLE),
	m_output(riffOutput)
{}

bool RiffWriter::startChunk(const QString &identifier, const QString &subIdentifier)
{
	if (m_state != IDLE) {
		qWarning("%s: Trying to start new chunk while has state: %s", qPrintable(TAG),
				 qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		return false;
	}

	if (identifier.size() < IDENTIFIER_SIZE) {
		qWarning("%s: Identifier length is too small: %d", qPrintable(TAG), identifier.size());
		return false;
	}

	if ((identifier == RIFF_CHUNCK_IDENTIFIER || identifier == LIST_CHUNK_IDENTIFIER) &&
			subIdentifier.size() < IDENTIFIER_SIZE) {
		qWarning("%s: Sub-identifier length for chunk type: %s is too small", qPrintable(TAG), qPrintable(identifier));
		return false;
	}

	changeState(WRITING_CHUNK);

	if (m_output.write(identifier.toLocal8Bit().data(), IDENTIFIER_SIZE) < IDENTIFIER_SIZE) {
		qFatal("%s: Error writing chunk identifier: %s", qPrintable(TAG), qPrintable(identifier));
		changeState(FAILURE);
		return false;
	}

	m_chunkLengthFieldPosition = m_output.pos();
	m_writtenDataSize = 0;

	if (!m_output.seek(m_chunkLengthFieldPosition + LENGTH_FIELD_SIZE)) {
		qFatal("%s: Error seeking over chunk length field", qPrintable(TAG));
		changeState(FAILURE);
		return false;
	}

	if ((identifier == RIFF_CHUNCK_IDENTIFIER || identifier == LIST_CHUNK_IDENTIFIER)) {
		if (writeData(subIdentifier.toLocal8Bit().data(), IDENTIFIER_SIZE) < IDENTIFIER_SIZE) {
			qFatal("%s: Error writing sub-identifier: %s", qPrintable(TAG), qPrintable(subIdentifier));
			return false;
		}
	}

	return true;
}

bool RiffWriter::finishChunk()
{
	if (m_state != WRITING_CHUNK) {
		qWarning("%s: Trying to finish chunk while has state: %s", qPrintable(TAG),
				 qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		return false;
	}

	m_tailPosition = m_output.pos();

	if (!m_output.seek(m_chunkLengthFieldPosition)) {
		qFatal("%s: Error seeking to chunk length field", qPrintable(TAG));
		changeState(FAILURE);
		return false;
	}

	quint32 length = m_writtenDataSize;
	if (m_output.write((const char *) &length, LENGTH_FIELD_SIZE) < LENGTH_FIELD_SIZE) {
		qFatal("%s: Error writing chunk length field", qPrintable(TAG));
		changeState(FAILURE);
		return false;
	}

	if (!m_output.seek(m_tailPosition)) {
		qFatal("%s: Error seeking back to tail", qPrintable(TAG));
		changeState(FAILURE);
		return false;
	}

	changeState(IDLE);

	return true;
}

qint64 RiffWriter::writeData(const char *data, qint64 maxSize)
{
	qint64 result = m_output.write(data, maxSize);
	if (result != maxSize) {
		qFatal("%s: Error writing data; requested size: %lld; actual written: %lld", qPrintable(TAG), maxSize, result);
		changeState(FAILURE);
		return result;
	}

	m_writtenDataSize += result;

	return result;
}

bool RiffWriter::seek(qint64 pos)
{
	return m_output.seek(pos);
}

qint64 RiffWriter::pos() const
{
	return m_output.pos();
}

void RiffWriter::changeState(State newState)
{
	if (m_state == newState) {
		qFatal("%s: Trying to change state to %s but already has that state", qPrintable(TAG),
			   qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		throw AlreadyHasStateException();
	}

	qInfo("%s: State %s -> %s", qPrintable(TAG), qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)),
		  qPrintable(QMetaEnum::fromType<State>().valueToKey(newState)));

	m_state = newState;
}
