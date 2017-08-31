#ifndef SOUNDBUFFERPARAMS_H
#define SOUNDBUFFERPARAMS_H


#include <QtGlobal>

struct SoundBufferParams
{
	quint32 sampleRate;
	int numberOfChannels;
	int bitsPerSample;
	int numberOfSamples;
};

#endif // SOUNDBUFFERPARAMS_H
