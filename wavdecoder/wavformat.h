#ifndef WAVFORMAT_H
#define WAVFORMAT_H


#include <QMetaEnum>

class WavFormat
{
public:
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
