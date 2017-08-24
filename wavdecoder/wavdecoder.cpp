#include "wavdecoder.h"
#include <QDebug>
#include <QMetaEnum>

const QString WavDecoder::TAG = "WavDecoder";
const QString WavDecoder::WAVE_IDENTIFIER = "WAVE";
const QString WavDecoder::FORMAT_IDENTIFIER = "fmt ";
const QString WavDecoder::DATA_IDENTIFIER = "data";

WavDecoder::WavDecoder(QIODevice &ioDevice, QObject *parent) :
	QObject(parent),
	m_ioDevice(ioDevice),
	m_wavReader(nullptr)
{}

WavDecoder::~WavDecoder()
{
	if (m_wavReader != nullptr)
		delete m_wavReader;
}

bool WavDecoder::init()
{
	if (m_wavReader != nullptr) {
		qDebug() << TAG << "Already initialized";
		return false;
	}

	RiffReader riffReader(m_ioDevice);
	bool isWaveChunkFound = false;
	while (riffReader.nextChunk() == RiffReader::OK) {
		if (riffReader.chunkHeader().identifier() == RiffChunkHeader::RIFF_IDENTIFIER &&
				riffReader.subIdentifier() == WAVE_IDENTIFIER) {
			qDebug() << TAG << "Wave chunk found";
			isWaveChunkFound = true;
			break;
		}
	}
	if (!isWaveChunkFound) {
		qDebug() << TAG << "Wave chunk not found";
		return false;
	}

	m_wavReader = new RiffReader(m_ioDevice);

	bool isFormatChunkFound = false;
	while (m_wavReader->nextChunk() == RiffReader::OK) {
		if (m_wavReader->chunkHeader().identifier() == FORMAT_IDENTIFIER) {
			qDebug() << TAG << "Format chunk found";
			isFormatChunkFound = true;

			m_wavReader->readData((char *) &m_format.code, 2);
			m_wavReader->readData((char *) &m_format.numberOfChannels, 2);
			m_wavReader->readData((char *) &m_format.sampleRate, 4);
			m_wavReader->readData((char *) &m_format.avgBytesPerSecond, 4);
			m_wavReader->readData((char *) &m_format.dataBlockSize, 2);
			m_wavReader->readData((char *) &m_format.bitsPerSample, 2);
			m_wavReader->readData((char *) &m_format.extensionSize, 2);
			m_wavReader->readData((char *) &m_format.numberOfValidBits, 2);
			m_wavReader->readData((char *) &m_format.speakerPositionMask, 4);
			m_wavReader->readData((char *) &m_format.subformat, 16);

			qDebug() << TAG << "\tCode" << QMetaEnum::fromType<Code>().valueToKey(m_format.code);
			qDebug() << TAG << "\tNumber of channels" << m_format.numberOfChannels;
			qDebug() << TAG << "\tSamling rate" << m_format.sampleRate;
			qDebug() << TAG << "\tAverage bytes per second" << m_format.avgBytesPerSecond;
			qDebug() << TAG << "\tData block size" << m_format.dataBlockSize;
			qDebug() << TAG << "\tBits per sample" << m_format.bitsPerSample;
			qDebug() << TAG << "\tExtension size" << m_format.extensionSize;
			qDebug() << TAG << "\tNumber of valid bits" << m_format.numberOfValidBits;
			qDebug() << TAG << "\tSpeaker position mask" << m_format.speakerPositionMask;

			break;
		}
	}
	if (!isFormatChunkFound) {
		qDebug() << TAG << "Format chunk not found";
		return false;
	}

	if (m_format.code != PCM) {
		qDebug() << TAG << "Unsupported data encoding" << QMetaEnum::fromType<Code>().valueToKey(m_format.code);
		return false;
	}

	while (m_wavReader->nextChunk() == RiffReader::OK) {
		if (m_wavReader->chunkHeader().identifier() == DATA_IDENTIFIER) {
			qDebug() << TAG << "Data chunk found";
			return true;
		}
	}
	return false;
}

quint32 WavDecoder::decode(char *buffer, quint32 size)
{
	return m_wavReader->readData(buffer, size);
}
