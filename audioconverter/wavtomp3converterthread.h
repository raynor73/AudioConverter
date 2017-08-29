#ifndef WAVTOMP3CONVERTERTHREAD_H
#define WAVTOMP3CONVERTERTHREAD_H

#include "converterthread.h"

class WavToMp3ConverterThread : public ConverterThread
{
	Q_OBJECT

public:
	struct Settings
	{
		int bitrate;
	};

	WavToMp3ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, Settings settings,
							QObject *parent = 0);

protected:
	void run() override;

private:
	static const QString TAG;
	static const int BUFFER_SIZE = 102400;

	Settings m_settings;
};

#endif // WAVTOMP3CONVERTERTHREAD_H
