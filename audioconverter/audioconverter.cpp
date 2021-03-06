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

#include "audioconverter.h"
#include <QtGlobal>
#include <QMetaEnum>
#include <QApplication>
#include "wavtomp3converterthread.h"
#include "mp3towavconverterthread.h"

const QString AudioConverter::TAG = "AudioConverter";

AudioConverter::AudioConverter(QObject *parent) :
	QObject(parent),
	m_state(IDLE),
	m_converterThread(nullptr)
{
	qRegisterMetaType<State>("State");
	qRegisterMetaType<ConvertionResultInfo>("ConvertionResultInfo");
}

AudioConverter::~AudioConverter()
{
	if (m_converterThread != nullptr) {
		m_converterThread->wait();
		delete m_converterThread;
	}
}

void AudioConverter::convert(const QStringList &sourceFilePaths, const QString &destDirPath, Settings settings)
{
	if (m_state != IDLE) {
		qWarning("%s: unable to start converting while has state: %s", qPrintable(TAG),
				 qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		return;
	}

	if (sourceFilePaths.size() == 0) {
		qWarning("%s: empty source paths list", qPrintable(TAG));
		return;
	}

	changeState(WORKING);

	if (m_converterThread != nullptr)
		delete m_converterThread;

	if (settings.convertionWay == WAV_TO_MP3) {
		WavToMp3ConverterThread::Settings wavToMp3Settings;
		wavToMp3Settings.bitrate = settings.mp3Bitrate;
		m_converterThread = new WavToMp3ConverterThread(sourceFilePaths, destDirPath, wavToMp3Settings);
	} else {
		Mp3ToWavConverterThread::Settings mp3ToWavSettings;
		mp3ToWavSettings.sampleRate = settings.wavSampleRate;
		mp3ToWavSettings.bitsPerSameple = settings.wavBitsPerSample;
		m_converterThread = new Mp3ToWavConverterThread(sourceFilePaths, destDirPath, mp3ToWavSettings);
	}

	connect(m_converterThread, &ConverterThread::progressChanged, this, &AudioConverter::progressChanged);
	connect(m_converterThread, &ConverterThread::finished, this, [this]() {
		changeState(IDLE);
	});
	connect(m_converterThread, &ConverterThread::convertionResultAdded, this,
			[this](ConverterThread::ConvertionResultInfo result) {
		m_convertionResults += ConvertionResultInfo(result);
		emit convertionResultAdded(m_convertionResults.last());
	});
	m_converterThread->start();
}

void AudioConverter::cancel()
{
	if (m_state != WORKING) {
		qWarning("%s: unable to cancel converting while has state: %s", qPrintable(TAG),
				 qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		return;
	}

	m_converterThread->requestInterruption();
	m_converterThread->wait();
}

void AudioConverter::changeState(State newState)
{
	if (m_state == newState) {
		qFatal("%s: Trying to change state to %s but already has that state", qPrintable(TAG),
			   qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)));
		qApp->exit(1);
	}

	qInfo("%s: State %s -> %s", qPrintable(TAG), qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)),
		  qPrintable(QMetaEnum::fromType<State>().valueToKey(newState)));

	m_state = newState;

	emit stateChanged(m_state);
}
