#include "soundbuffer.h"

SoundBuffer::SoundBuffer(SoundBufferParams params, QObject *parent) :
	QObject(parent),
	m_params(params)
{
	m_data = new unsigned char[params.bitsPerSample / 8 * params.numberOfChannels * params.numberOfSamples];
}

SoundBuffer::~SoundBuffer()
{
	delete[] m_data;
}
