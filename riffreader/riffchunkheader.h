/***********************************************************************************************************************
 * Audio Converter
 * Copyright (C) 2017  Igor Lapin
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************************************************/

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
