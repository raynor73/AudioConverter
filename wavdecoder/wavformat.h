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

#ifndef WAVFORMAT_H
#define WAVFORMAT_H


#include <QtGlobal>

struct WavFormat
{
	quint16 code;
	quint16 numberOfChannels;
	quint32 sampleRate;
	quint32 avgBytesPerSecond;
	quint16 dataBlockSize;
	quint16 bitsPerSample;
	quint16 extensionSize;
	quint16 numberOfValidBits;
	quint32 speakerPositionMask;
	char subformat[16];
};

#endif // WAVFORMAT_H
