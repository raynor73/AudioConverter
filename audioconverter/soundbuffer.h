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
