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

private:
	SoundBuffer *m_sourceBuffer;
	SoundBuffer *m_destBuffer;
	int m_samplesAvailabe;
	float m_resamplingFactor;
};

#endif // RESAMPLER_H
