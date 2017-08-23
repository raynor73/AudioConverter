#include "soundbuffer.h"

SoundBuffer::SoundBuffer(SoundBufferParams params, QObject *parent) :
	QObject(parent),
	m_params(params)
{
	m_data = new char[params.resolutionMeasuredInBytes() * params.numberOfChannels() * params.numberOfSamples()];
}

SoundBuffer::~SoundBuffer()
{
	delete[] m_data;
}
