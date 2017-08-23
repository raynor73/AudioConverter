#ifndef SOUNDBUFFERPARAMS_H
#define SOUNDBUFFERPARAMS_H


class SoundBufferParams
{
public:
	SoundBufferParams(int sampleRate, int numberOfChannels, int resolutionMeasuredInBytes, int numberOfSamples) :
		m_sampleRate(sampleRate),
		m_numberOfChannels(numberOfChannels),
		m_resolutionMeasuredInBytes(resolutionMeasuredInBytes),
		m_numberOfSamples(numberOfSamples)
	{}

	int sampleRate() const { return m_sampleRate; }
	int numberOfChannels() const { return m_numberOfChannels; }
	int resolutionMeasuredInBytes() const { return m_resolutionMeasuredInBytes; }
	int numberOfSamples() const { return m_numberOfSamples; }

private:
	int m_sampleRate;
	int m_numberOfChannels;
	int m_resolutionMeasuredInBytes;
	int m_numberOfSamples;
};

#endif // SOUNDBUFFERPARAMS_H
