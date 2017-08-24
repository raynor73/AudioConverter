#include "resampler.h"

Resampler::Resampler(SoundBufferParams sourceBufferParams, SoundBufferParams destBufferParams, QObject *parent) :
	QObject(parent)
{
	m_sourceBuffer = new SoundBuffer(sourceBufferParams);
	m_destBuffer = new SoundBuffer(destBufferParams);
}

void Resampler::resample(int)
{
	if (m_sourceBuffer->params().sampleRate() > m_destBuffer->params().sampleRate()) {

	} else if (m_sourceBuffer->params().sampleRate() < m_destBuffer->params().sampleRate()) {

	} else {

	}
}

Resampler::~Resampler()
{
	delete m_sourceBuffer;
	delete m_destBuffer;
}
