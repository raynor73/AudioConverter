#ifndef RESAMPLER_H
#define RESAMPLER_H

#include <QObject>
#include "soundbuffer.h"

class Resampler : public QObject
{
	Q_OBJECT

public:
	Resampler(SoundBufferParams sourceBufferParams, SoundBufferParams destBufferParams, QObject *parent = 0);
	virtual ~Resampler();

	void resample(int numberOfSamples);
	SoundBuffer &sourceBuffer() { return *m_sourceBuffer; }
	SoundBuffer &destBuffer() { return *m_destBuffer; }

private:
	SoundBuffer *m_sourceBuffer;
	SoundBuffer *m_destBuffer;
};

#endif // RESAMPLER_H
