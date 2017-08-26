#include "audioconverter.h"
#include <QtGlobal>
#include <QMetaEnum>
#include <QApplication>
#include <wavtomp3converterthread.h>

const QString AudioConverter::TAG = "AudioConverter";

AudioConverter::AudioConverter(QObject *parent) :
	QObject(parent),
	m_state(IDLE),
	m_converterThread(nullptr)
{
	qRegisterMetaType<State>("State");
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

	WavToMp3ConverterThread::Settings wavToMp3Settings;
	wavToMp3Settings.bitrate = settings.mp3Bitrate;
	m_converterThread = new WavToMp3ConverterThread(sourceFilePaths, destDirPath, wavToMp3Settings);
	connect(m_converterThread, &ConverterThread::progressChanged, this, &AudioConverter::progressChanged);
	connect(m_converterThread, &ConverterThread::finished, this, [this]() {
		changeState(IDLE);
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
