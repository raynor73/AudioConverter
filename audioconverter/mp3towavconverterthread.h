#ifndef MP3TOWAVCONVERTERTHREAD_H
#define MP3TOWAVCONVERTERTHREAD_H

#include "converterthread.h"
#include <QException>

class Mp3ToWavConverterThread : public ConverterThread
{
	Q_OBJECT

public:
	struct Settings
	{
		int sampleRate;
		int bitsPerSameple;
	};

	class OutOfMemoryException : QException {};

	Mp3ToWavConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, Settings settings,
							QObject *parent = 0);

protected:
	void run() override;

private:
	static const QString TAG;
	static const int BUFFER_SIZE = 102400;

	Settings m_settings;

	void merge(qint16 *interleavedBuffer, qint16 *leftChannelBuffer, qint16 *rightChannleBuffer, int numberOfSamples);
};

#endif // MP3TOWAVCONVERTERTHREAD_H
