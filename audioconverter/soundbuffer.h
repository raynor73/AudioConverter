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

#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include <QObject>
#include "soundbufferparams.h"

class SoundBuffer : public QObject
{
	Q_OBJECT

public:
	SoundBuffer(SoundBufferParams params, QObject *parent = 0);
	virtual ~SoundBuffer();

	SoundBufferParams params() const { return m_params; }
	unsigned char *data() { return m_data; }

private:
	SoundBufferParams m_params;
	unsigned char *m_data;
};

#endif // SOUNDBUFFER_H
