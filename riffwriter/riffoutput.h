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

#ifndef RIFFOUTPUT_H
#define RIFFOUTPUT_H

#include <QObject>
#include <QIODevice>
#include <QException>

class RiffWriter;

class RiffOutput : public QObject
{
	Q_OBJECT
public:
	class DeviceIsSequentialException : QException {};

	RiffOutput(QIODevice *ioDevice, QObject *parent = 0);
	RiffOutput(RiffWriter *riffWriter, QObject *parent = 0);

	qint64 write(const char *data, qint64 maxSize);
	bool seek(qint64 pos);
	qint64 pos() const;

private:
	QIODevice *m_ioDevice;
	RiffWriter *m_riffWriter;
};

#endif // RIFFOUTPUT_H
