#include "resampler.h"
#include <cmath>
#include <cstring>

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
	m_samplesAvailabe = numberOfSamples;

	SoundBufferParams sourceBufferParams = m_sourceBuffer->params();
	SoundBufferParams destBufferParams = m_destBuffer->params();

	const int bufferSize = destBufferParams.numberOfSamples * sourceBufferParams.numberOfChannels;
	float *buffer = new float[bufferSize];
	if (sourceBufferParams.sampleRate > destBufferParams.sampleRate) {
		switch (sourceBufferParams.bitsPerSample) {
		case 8: {
			unsigned char *sourceBuffer = m_sourceBuffer->data();
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[bufferIndex] = (float(sourceBuffer[i]) - 127.0f) / 128.0f;
				} else {
					buffer[bufferIndex * 2] = (float(sourceBuffer[i * 2]) - 127.0f) / 128.0f;
					buffer[bufferIndex * 2 + 1] = (float(sourceBuffer[i * 2 + 1]) - 127.0f) / 128.0f;
				}
			}
			break;
		}

		case 16: {
			quint16 *sourceBuffer = (quint16 *) m_sourceBuffer->data();
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					buffer[bufferIndex] = float(sourceBuffer[i]) / 32768.0f;
				} else {
					buffer[bufferIndex * 2] = float(sourceBuffer[i * 2]) / 32768.0f;
					buffer[bufferIndex * 2 + 1] = float(sourceBuffer[i * 2 + 1]) / 32768.0f;
				}
			}
			break;
		}

		case 24: {
			unsigned char *sourceBuffer = m_sourceBuffer->data();
			for (int i = 0; i < numberOfSamples; i++) {
				int bufferIndex = float(i) * m_resamplingFactor;
				if (sourceBufferParams.numberOfChannels == 1) {
					quint32 value;
					std::memcpy(&value, sourceBuffer + i * 3, 3);
					buffer[bufferIndex] = float(value) / 16777216.0f;
				} else {
					quint32 left, right;
					std::memcpy(&left, sourceBuffer + i * 6, 3);
					std::memcpy(&right, sourceBuffer+ i * 6 + 3, 3);
					buffer[bufferIndex * 2] = float(left) / 16777216.0f;
					buffer[bufferIndex * 2 + 1] = float(right) / 16777216.0f;
				}
			}
			break;
		}

		default:
			throw UnsupportedBitrateException();
		}
	}
	delete[] buffer;
	/*if (sourceBufferParams.bitsPerSample > destBufferParams.bitsPerSample) {
	} else {
	}*/
}
