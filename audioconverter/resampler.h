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

#ifndef RESAMPLER_H
#define RESAMPLER_H

#include <QObject>
#include "soundbuffer.h"
#include <QException>

class Resampler : public QObject
{
	Q_OBJECT

public:
	class UnsupportedBitrateException : QException {};
	class UnsupportedNumberOfChannelsException : QException {};

	Resampler(SoundBufferParams sourceBufferParams, SoundBufferParams destBufferParams, QObject *parent = 0);
	~Resampler();

	void resample(int numberOfSamples);
	SoundBuffer &sourceBuffer() { return *m_sourceBuffer; }
	SoundBuffer &destBuffer() { return *m_destBuffer; }

	int sourceSamplesAvailable() const { return m_sourceSamplesAvailabe; }
	int destSamplesAvailable() const { return m_destSamplesAvailabe; }

private:
	SoundBuffer *m_sourceBuffer;
	SoundBuffer *m_destBuffer;
	int m_sourceSamplesAvailabe;
	int m_destSamplesAvailabe;
	float m_resamplingFactor;
};

#endif // RESAMPLER_H
