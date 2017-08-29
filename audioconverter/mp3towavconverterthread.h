#ifndef MP3TOWAVCONVERTERTHREAD_H
#define MP3TOWAVCONVERTERTHREAD_H

#include "converterthread.h"

class Mp3ToWavConverterThread : public ConverterThread
{
	Q_OBJECT

public:
	struct Settings
	{
		int sampleRate;
		int bitsPerSameple;
	};

	Mp3ToWavConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, Settings settings,
							QObject *parent = 0);

protected:
	void run() override;

private:
	static const QString TAG;
	static const int BUFFER_SIZE = 102400;

	Settings m_settings;
};

#endif // MP3TOWAVCONVERTERTHREAD_H
