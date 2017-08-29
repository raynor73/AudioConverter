#ifndef RIFFCHUNKHEADER_H
#define RIFFCHUNKHEADER_H


#include <QtGlobal>
#include <QString>

class RiffChunkHeader
{
public:
	RiffChunkHeader() {}
	RiffChunkHeader(char *identifier, quint32 dataLength);

	static const QString RIFF_IDENTIFIER;
	static const QString LIST_IDENTIFIER;

	QString identifier() const { return QString::fromLatin1(m_identifier, sizeof(m_identifier)); }
	quint32 dataLength() const { return m_dataLength; }

private:
	char m_identifier[4];
	quint32 m_dataLength;
};

#endif // RIFFCHUNKHEADER_H
