/***********************************************************************************************************************
 * Audio Converter
 * Copyright (C) 2017  Igor Lapin
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************************************************/

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
