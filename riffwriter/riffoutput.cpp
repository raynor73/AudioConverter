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
