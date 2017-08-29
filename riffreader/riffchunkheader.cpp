#include "riffchunkheader.h"
#include <cstring>

const QString RiffChunkHeader::RIFF_IDENTIFIER = "RIFF";
const QString RiffChunkHeader::LIST_IDENTIFIER = "LIST";

RiffChunkHeader::RiffChunkHeader(char *identifier, quint32 dataLength)
{
	std::memcpy(m_identifier, identifier, sizeof(m_identifier));
	m_dataLength = dataLength;
}
