#include "converterthread.h"

float ConverterThread::calculateProgress()
{
	if (m_totalFiles == 0)
		return 0;

	return	float(m_currentFileIndex + m_currentFileProgress) / m_totalFiles;
}
