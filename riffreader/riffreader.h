#ifndef RIFFREADER_H
#define RIFFREADER_H

#include <QObject>
#include <QIODevice>
#include "riffchunkheader.h"

class RiffReader : public QObject
{
	Q_OBJECT
public:
	static const QString TAG;

	enum ChunkReadResult { OK, NO_CHUNK, ERROR };

	RiffReader(QIODevice &ioDevice, QObject *parent = 0);

	RiffChunkHeader chunkHeader() const { return m_currentChunkHeader; }
	QString subIdentifier() const { return QString::fromLatin1(m_subIdentifier, sizeof(m_subIdentifier)); }
	ChunkReadResult nextChunk();
	quint32 readData(char *buffer, quint32 size);

private:
	QIODevice &m_ioDevice;
	RiffChunkHeader m_currentChunkHeader;
	char m_subIdentifier[4];
	quint32 m_availableDataLeft;
};

#endif // RIFFREADER_H
