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

#include "riffreader.h"
#include <cstring>
#include <QDebug>

const QString RiffReader::TAG = "RiffReader";

RiffReader::RiffReader(QIODevice &ioDevice, QObject *parent) :
	QObject(parent),
	m_ioDevice(ioDevice),
	m_availableDataLeft(0)
{
	std::memset(&m_subIdentifier, 0, sizeof(m_subIdentifier));
	std::memset(&m_currentChunkHeader, 0, sizeof(RiffChunkHeader));
}

RiffReader::ChunkReadResult RiffReader::nextChunk()
{
	if (m_availableDataLeft > 0) {
		auto padding = 0;
		if (m_currentChunkHeader.dataLength() % 2 != 0)
			padding = 1;

		m_ioDevice.seek(m_ioDevice.pos() + m_availableDataLeft + padding);
		m_availableDataLeft = 0;
	}

	if (m_ioDevice.atEnd()) {
		qDebug() << TAG << "No more chunks left";
		return NO_CHUNK;
	}

	if ((std::size_t) m_ioDevice.read(reinterpret_cast<char *>(&m_currentChunkHeader), sizeof(RiffChunkHeader)) < sizeof(RiffChunkHeader)) {
		qDebug() << TAG << "Error reading chunk header";
		return ERROR;
	}

	qDebug() << TAG << "Found chunk";
	qDebug() << TAG << "Identifier:" << m_currentChunkHeader.identifier();
	qDebug() << TAG << "Data length:" << m_currentChunkHeader.dataLength();

	m_availableDataLeft = m_currentChunkHeader.dataLength();

	if (m_currentChunkHeader.identifier() == RiffChunkHeader::RIFF_IDENTIFIER ||
			m_currentChunkHeader.identifier() == RiffChunkHeader::LIST_IDENTIFIER) {
		if ((std::size_t) m_ioDevice.read(reinterpret_cast<char *>(&m_subIdentifier), sizeof(m_subIdentifier)) < sizeof(m_subIdentifier)) {
			qDebug() << TAG << "Error reading chunk header";
			return ERROR;
		}

		m_availableDataLeft -= sizeof(m_subIdentifier);

		qDebug() << TAG << "Sub-identifier:" << subIdentifier();
	}

	return OK;
}

quint32 RiffReader::readData(char *buffer, quint32 size)
{
	if (m_availableDataLeft == 0) {
		qDebug() << "No more data left";
		return 0;
	}

	auto bytesRead = m_ioDevice.read(buffer, size);
	if (bytesRead < 0) {
		qDebug() << TAG << "Error reading data from chunk";
		return -1;
	}
	m_availableDataLeft -= bytesRead;

	return bytesRead;
}
