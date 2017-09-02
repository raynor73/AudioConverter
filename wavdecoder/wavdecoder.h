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

#ifndef WAVREADER_H
#define WAVREADER_H

#include <QObject>
#include <QIODevice>
#include <riffreader.h>
#include "wavformat.h"

class WavDecoder : public QObject
{
	Q_OBJECT

public:
	enum Code { PCM = 0x0001, IEEE_FLOAT = 0x0003, ALAW = 0x0006, MULAW = 0x0007, EXTENSIBLE = 0xFFFE };
	Q_ENUM(Code)

	WavDecoder(QIODevice &ioDevice, QObject *parent = 0);
	virtual ~WavDecoder();

	bool init();
	WavFormat format() const { return m_format; }
	quint32 decode(char *buffer, quint32 size);

private:
	static const QString TAG;

	static const QString WAVE_IDENTIFIER;
	static const QString FORMAT_IDENTIFIER;
	static const QString DATA_IDENTIFIER;

	QIODevice &m_ioDevice;
	WavFormat m_format;
	RiffReader *m_wavReader;
};

#endif // WAVREADER_H
