#ifndef RIFFWRITER_H
#define RIFFWRITER_H

#include <QObject>
#include <QException>

class RiffOutput;

class RiffWriter : public QObject
{
	Q_OBJECT

public:
	class AlreadyHasStateException : QException {};

	static const QString TAG;
	static const QString RIFF_CHUNCK_IDENTIFIER;
	static const QString LIST_CHUNK_IDENTIFIER;

	enum State { IDLE, SEEKING, WRITING_CHUNK, FAILURE };
	Q_ENUM(State)

	RiffWriter(RiffOutput &riffOutput, QObject *parent = 0);

	bool startChunk(const QString &identifier, const QString &subIdentifier = QString());
	bool finishChunk();
	qint64 writeData(const char *data, qint64 maxSize);
	bool seek(qint64 pos);
	qint64 pos() const;

private:
	static const int IDENTIFIER_SIZE = 4;
	static const int LENGTH_FIELD_SIZE = 4;

	State m_state;
	RiffOutput &m_output;

	qint64 m_chunkLengthFieldPosition;
	qint64 m_tailPosition;
	qint64 m_writtenDataSize;

	void changeState(State newState);
};

#endif // RIFFWRITER_H
