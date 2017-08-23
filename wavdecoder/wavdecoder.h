#ifndef WAVREADER_H
#define WAVREADER_H

#include <QObject>
#include <QIODevice>
#include "wavformat.h"

class WavDecoder : public QObject
{
	Q_OBJECT

public:
	WavDecoder(QIODevice &ioDevice, QObject *parent = 0);

	bool init();
	WavFormat format();
	quint32 decode(char *buffer, quint32 size);
};

#endif // WAVREADER_H
