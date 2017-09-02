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
