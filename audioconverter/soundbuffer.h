#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include <QObject>

class SoundBuffer : public QObject
{
	Q_OBJECT
public:
	explicit SoundBuffer(QObject *parent = 0);

signals:

public slots:
};

#endif // SOUNDBUFFER_H
