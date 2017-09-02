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

#include "wavencoder.h"
#include <wavformat.h>

const QString WavEncoder::TAG = "WavEncoder";
const QString WavEncoder::WAVE_IDENTIFIER = "WAVE";
const QString WavEncoder::FORMAT_IDENTIFIER = "fmt ";
const QString WavEncoder::DATA_IDENTIFIER = "data";

bool WavEncoder::init()
{
	m_riffOutput = QSharedPointer<RiffOutput>::create(&m_ioDevice);
	m_riffWriter = QSharedPointer<RiffWriter>::create(*m_riffOutput);

	if (!m_riffWriter->startChunk(RiffWriter::RIFF_CHUNCK_IDENTIFIER, WAVE_IDENTIFIER)) {
		qFatal("%s: Failed to start RIFF chunk", qPrintable(TAG));
		return false;
	}

	m_wavOutput = QSharedPointer<RiffOutput>::create(m_riffWriter.data());
	m_wavWriter = QSharedPointer<RiffWriter>::create(*m_wavOutput);

	if (!m_wavWriter->startChunk(FORMAT_IDENTIFIER)) {
		qFatal("%s: Failed to start WAV format chunk", qPrintable(TAG));
		return false;
	}

	WavFormat format;
	format.code = m_config.format;
	format.numberOfChannels = m_config.numberOfChannels;
	format.sampleRate = m_config.sampleRate;
	format.avgBytesPerSecond = m_config.sampleRate * m_config.bitsPerSample / 8 * m_config.numberOfChannels;
	format.dataBlockSize = m_config.bitsPerSample / 8 * m_config.numberOfChannels;
	format.bitsPerSample = m_config.bitsPerSample;

	if (m_wavWriter->writeData((const char *) &format, PARTIAL_FORMAT_SIZE) < PARTIAL_FORMAT_SIZE) {
		qFatal("%s: Failed to write WAV format data", qPrintable(TAG));
		return false;
	}

	if (!m_wavWriter->finishChunk()) {
		qFatal("%s: Failed to finish WAV format chunk", qPrintable(TAG));
		return false;
	}

	if (!m_wavWriter->startChunk(DATA_IDENTIFIER)) {
		qFatal("%s: Failed to start WAV data chunk", qPrintable(TAG));
		return false;
	}

	return true;
}

quint32 WavEncoder::encode(char *buffer, quint32 size)
{
	qint64 result = m_wavWriter->writeData(buffer, size);
	if (result < size) {
		qFatal("%s: Failed to write %d byte(s) of WAV data, actually wrote %lld byte(s)", qPrintable(TAG), size,
			   result);
	}

	return result;
}

bool WavEncoder::finish()
{
	if (!m_wavWriter->finishChunk()) {
		qFatal("%s: Failed to finish WAV data chunk", qPrintable(TAG));
		return false;
	}

	if (!m_riffWriter->finishChunk()) {
		qFatal("%s: Failed to finish RIFF chunk", qPrintable(TAG));
		return false;
	}

	return true;
}
