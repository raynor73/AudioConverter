#include "resampler.h"
#include <cmath>
#include <cstring>
#include <QDebug>

Resampler::Resampler(SoundBufferParams sourceBufferParams, SoundBufferParams destBufferParams, QObject *parent) :
	QObject(parent)
{
	m_resamplingFactor = float(destBufferParams.sampleRate) / float(sourceBufferParams.sampleRate);
	m_sourceBuffer = new SoundBuffer(sourceBufferParams);
	destBufferParams.numberOfSamples = float(sourceBufferParams.numberOfSamples) * m_resamplingFactor;
	m_destBuffer = new SoundBuffer(destBufferParams);

	if (sourceBufferParams.numberOfChannels < 1 || sourceBufferParams.numberOfChannels > 2)
		throw UnsupportedNumberOfChannelsException();

	if (destBufferParams.numberOfChannels < 1 || destBufferParams.numberOfChannels > 2)
		throw UnsupportedNumberOfChannelsException();
}

Resampler::~Resampler()
{
	delete m_sourceBuffer;
	delete m_destBuffer;
}

void Resampler::resample(int numberOfSamples)
{
	m_sourceSamplesAvailabe = numberOfSamples;
	m_destSamplesAvailabe = numberOfSamples * m_resamplingFactor;
	if (m_destSamplesAvailabe > m_destBuffer->params().numberOfSamples)
		m_destSamplesAvailabe = m_destBuffer->params().numberOfSamples;

	SoundBufferParams sourceBufferParams = m_sourceBuffer->params();
	SoundBufferParams destBufferParams = m_destBuffer->params();

	const int bufferSize = destBufferParams.numberOfSamples * sourceBufferParams.numberOfChannels;
	float *buffer = new float[bufferSize];

	switch (sourceBufferParams.bitsPerSample) {
	case 8: {
		unsigned char *sourceBuffer = m_sourceBuffer->data();
		if (sourceBufferParams.sampleRate >= destBufferParams.sampleRate) {
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[bufferIndex] = (float(sourceBuffer[i]) - 127.0f) / 128.0f;
				} else {
					buffer[bufferIndex * 2] = (float(sourceBuffer[i * 2]) - 127.0f) / 128.0f;
					buffer[bufferIndex * 2 + 1] = (float(sourceBuffer[i * 2 + 1]) - 127.0f) / 128.0f;
				}
			}
		} else {
			for (int i = 0; i < m_destSamplesAvailabe; i++) {
				int bufferIndex = float(i) / m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[i] = (float(sourceBuffer[bufferIndex]) - 127.0f) / 128.0f;
				} else {
					buffer[i * 2] = (float(sourceBuffer[bufferIndex * 2]) - 127.0f) / 128.0f;
					buffer[i * 2 + 1] = (float(sourceBuffer[bufferIndex * 2 + 1]) - 127.0f) / 128.0f;
				}
			}
		}
		break;
	}

	case 16: {
		qint16 *sourceBuffer = (qint16 *) m_sourceBuffer->data();
		if (sourceBufferParams.sampleRate >= destBufferParams.sampleRate) {
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[bufferIndex] = float(sourceBuffer[i]) / 32768.0f;
				} else {
					buffer[bufferIndex * 2] = float(sourceBuffer[i * 2]) / 32768.0f;
					buffer[bufferIndex * 2 + 1] = float(sourceBuffer[i * 2 + 1]) / 32768.0f;
				}
			}
		} else {
			for (int i = 0; i < m_destSamplesAvailabe; i++) {
				int bufferIndex = float(i) / m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[i] = float(sourceBuffer[bufferIndex]) / 32768.0f;
				} else {
					buffer[i * 2] = float(sourceBuffer[bufferIndex * 2]) / 32768.0f;
					buffer[i * 2 + 1] = float(sourceBuffer[bufferIndex * 2 + 1]) / 32768.0f;
				}
			}
		}
		break;
	}

	case 24: {
		unsigned char *sourceBuffer = m_sourceBuffer->data();
		if (sourceBufferParams.sampleRate >= destBufferParams.sampleRate) {
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					qint32 value;
					std::memcpy(&value, sourceBuffer + i * 3, 3);
					if (value & 0x00800000)
						value |= 0xff000000;
					buffer[bufferIndex] = float(value) / 8388608.0f;
				} else {
					qint32 left, right;
					std::memcpy(&left, sourceBuffer + i * 6, 3);
					std::memcpy(&right, sourceBuffer+ i * 6 + 3, 3);
					if (left & 0x00800000)
						left |= 0xff000000;
					if (right & 0x00800000)
						right |= 0xff000000;
					buffer[bufferIndex * 2] = float(left) / 8388608.0f;
					buffer[bufferIndex * 2 + 1] = float(right) / 8388608.0f;
				}
			}
		} else {
			for (int i = 0; i < m_destSamplesAvailabe; i++) {
				int bufferIndex = float(i) / m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					qint32 value;
					std::memcpy(&value, sourceBuffer + bufferIndex * 3, 3);
					if (value & 0x00800000)
						value |= 0xff000000;
					buffer[i] = float(value) / 8388608.0f;
				} else {
					qint32 left, right;
					std::memcpy(&left, sourceBuffer + bufferIndex * 6, 3);
					std::memcpy(&right, sourceBuffer+ bufferIndex * 6 + 3, 3);
					if (left & 0x00800000)
						left |= 0xff000000;
					if (right & 0x00800000)
						right |= 0xff000000;
					buffer[i * 2] = float(left) / 8388608.0f;
					buffer[i * 2 + 1] = float(right) / 8388608.0f;
				}
			}
		}
		break;
	}

	default:
		throw UnsupportedBitrateException();
	}

	switch (destBufferParams.bitsPerSample) {
	case 8: {
		unsigned char *destBuffer = m_destBuffer->data();
		for (int i = 0; i < m_destSamplesAvailabe; i++) {
			if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 1) {
				destBuffer[i] = (unsigned char) ((buffer[i] + 1.0f) / 2.0f * 255.0f);
			} else if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 2) {
				destBuffer[i * 2] = (unsigned char) ((buffer[i] + 1.0f) / 2.0f * 255.0f);
				destBuffer[i * 2 + 1] = (unsigned char) ((buffer[i] + 1.0f) / 2.0f * 255.0f);
			} else if (sourceBufferParams.numberOfChannels == 2 && destBufferParams.numberOfChannels == 1) {
				float value = (buffer[i * 2] + buffer[i * 2 + 1]) / 2.0f;
				destBuffer[i] = (unsigned char) ((value + 1.0f) / 2.0f * 255.0f);
			} else {
				destBuffer[i * 2] = (unsigned char) ((buffer[i * 2] + 1.0f) / 2.0f * 255.0f);
				destBuffer[i * 2 + 1] = (unsigned char) ((buffer[i * 2 + 1] + 1.0f) / 2.0f * 255.0f);
			}
		}
		break;
	}

	case 16: {
		qint16 *destBuffer = (qint16 *) m_destBuffer->data();
		for (int i = 0; i < m_destSamplesAvailabe; i++) {
			if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 1) {
				destBuffer[i] = (qint16) (buffer[i] * 32768.0f);
			} else if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 2) {
				destBuffer[i * 2] = (qint16) (buffer[i] * 32768.0f);
				destBuffer[i * 2 + 1] = (qint16) (buffer[i] * 32768.0f);
			} else if (sourceBufferParams.numberOfChannels == 2 && destBufferParams.numberOfChannels == 1) {
				float value = (buffer[i * 2] + buffer[i * 2 + 1]) / 2.0f;
				destBuffer[i] = (qint16) (value * 32768.0f);
			} else {
				destBuffer[i * 2] = (qint16) (buffer[i * 2] * 32768.0f);
				destBuffer[i * 2 + 1] = (qint16) (buffer[i * 2 + 1] * 32768.0f);
			}
		}
		break;
	}

	case 24: {
		unsigned char *destBuffer = m_destBuffer->data();
		for (int i = 0; i < m_destSamplesAvailabe; i++) {
			if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 1) {
				qint32 value = (qint32) (buffer[i] * 8388608.0f);
				std::memcpy(destBuffer + i * 3, &value, 3);
			} else if (sourceBufferParams.numberOfChannels == 1 && destBufferParams.numberOfChannels == 2) {
				qint32 value = (qint32) (buffer[i] * 8388608.0f);
				std::memcpy(destBuffer + i * 6, &value, 3);
				std::memcpy(destBuffer + i * 6 + 3, &value, 3);
			} else if (sourceBufferParams.numberOfChannels == 2 && destBufferParams.numberOfChannels == 1) {
				qint32 value = (qint32) (buffer[i * 2] + buffer[i * 2 + 1]) / 2.0f * 8388608.0f;
				std::memcpy(destBuffer + i * 3, &value, 3);
			} else {
				qint32 left, right;
				left = (qint32) (buffer[i * 2] * 8388608.0f);
				right = (qint32) (buffer[i * 2 + 1] * 8388608.0f);
				std::memcpy(destBuffer + i * 6, &left, 3);
				std::memcpy(destBuffer + i * 6 + 3, &right, 3);
			}
		}
		break;
	}

	default:
		throw UnsupportedBitrateException();
	}

	delete[] buffer;
}
