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
