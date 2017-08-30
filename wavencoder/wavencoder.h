#ifndef WAVENCODER_H
#define WAVENCODER_H

#include <QObject>
#include <QIODevice>
#include <QSharedPointer>
#include <riffwriter.h>
#include <riffoutput.h>
#include <QMetaEnum>

class WavEncoder : public QObject
{
	Q_OBJECT
public:
	enum Format { PCM = 0x0001 /*, IEEE_FLOAT = 0x0003, ALAW = 0x0006, MULAW = 0x0007, EXTENSIBLE = 0xFFFE*/ };
	Q_ENUM(Format)

	struct Config {
		Format format;
		quint16 numberOfChannels;
		quint32 sampleRate;
		quint16 bitsPerSample;
	};

	WavEncoder(QIODevice &ioDevice, const Config &config, QObject *parent = 0) :
		QObject(parent),
		m_ioDevice(ioDevice),
		m_config(config),
		m_isFinished(false)
	{}

	bool init();
	quint32 encode(char *buffer, quint32 size);
	bool finish();

private:
	static const QString TAG;

	static const int PARTIAL_FORMAT_SIZE = 16;
	static const QString WAVE_IDENTIFIER;
	static const QString FORMAT_IDENTIFIER;
	static const QString DATA_IDENTIFIER;

	QIODevice &m_ioDevice;
	QSharedPointer<RiffOutput> m_riffOutput;
	QSharedPointer<RiffWriter> m_riffWriter;
	QSharedPointer<RiffOutput> m_wavOutput;
	QSharedPointer<RiffWriter> m_wavWriter;
	Config m_config;
	bool m_isFinished;
};

#endif // WAVENCODER_H
