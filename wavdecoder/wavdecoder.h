#ifndef WAVREADER_H
#define WAVREADER_H

#include <QObject>
#include <QIODevice>
#include <riffreader.h>
#include "wavformat.h"

class WavDecoder : public QObject
{
	Q_OBJECT

public:
	enum Code { PCM = 0x0001, IEEE_FLOAT = 0x0003, ALAW = 0x0006, MULAW = 0x0007, EXTENSIBLE = 0xFFFE };
	Q_ENUM(Code)

	WavDecoder(QIODevice &ioDevice, QObject *parent = 0);
	virtual ~WavDecoder();

	bool init();
	WavFormat format() const { return m_format; }
	quint32 decode(char *buffer, quint32 size);

private:
	static const QString TAG;

	static const QString WAVE_IDENTIFIER;
	static const QString FORMAT_IDENTIFIER;
	static const QString DATA_IDENTIFIER;

	QIODevice &m_ioDevice;
	WavFormat m_format;
	RiffReader *m_wavReader;
};

#endif // WAVREADER_H
