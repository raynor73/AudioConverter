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
	char *data() { return m_data; }

private:
	SoundBufferParams m_params;
	char *m_data;
};

#endif // SOUNDBUFFER_H
