#include "audioconverter.h"
#include <QtGlobal>
#include <QMetaEnum>
#include <QApplication>

const QString AudioConverter::TAG = "AudioConverter";

AudioConverter::AudioConverter(QObject *parent) :
	QObject(parent),
	m_state(IDLE),
	m_converterThread(nullptr)
{}

AudioConverter::~AudioConverter()
{
	destroyThreadIfRequired();
}

void AudioConverter::convert(const QStringList &sourceFilePaths, const QString &destDirPath)
{
	if (m_state != IDLE) {
		qWarning("%s: unable to start converting while has state: %s", qPrintable(TAG),
				 qPrintable(QVariant(m_state).toString()));
		return;
	}

	if (sourceFilePaths.size() == 0) {
		qWarning("%s: empty source paths list", qPrintable(TAG));
		return;
	}

	changeState(WORKING);

	m_converterThread = new ConverterThread(sourceFilePaths, destDirPath);
	connect(m_converterThread, &ConverterThread::progressChanged, this, &AudioConverter::progressChanged);
	connect(m_converterThread, &ConverterThread::finished, [this]() {
		changeState(IDLE);
		destroyThreadIfRequired();
	});
	m_converterThread->start();
}

void AudioConverter::changeState(State newState)
{
	if (m_state == newState) {
		qFatal("%s: Trying to change state to %s but already has that state", qPrintable(TAG),
			   qPrintable(QVariant(m_state).toString()));
		qApp->exit(1);
	}

	qInfo("%s: State %s -> %s", qPrintable(TAG), qPrintable(QMetaEnum::fromType<State>().valueToKey(m_state)),
		  qPrintable(QMetaEnum::fromType<State>().valueToKey(newState)));

	m_state = newState;

	emit stateChanged(m_state);
}

void AudioConverter::destroyThreadIfRequired()
{
	if (m_converterThread != nullptr) {
		m_converterThread->wait();
		delete m_converterThread;
	}
}
