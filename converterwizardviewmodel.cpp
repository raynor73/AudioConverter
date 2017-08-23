#include "converterwizardviewmodel.h"
#include <QMetaEnum>

const QString ConverterWizardViewModel::CONVERTION_WAY_KEY = "wizard/start/convertion";
const QString ConverterWizardViewModel::MP3_BITRATE_INDEX_KEY = "wizard/mp3/bitrate_index";

ConverterWizardViewModel::ConverterWizardViewModel(QObject *parent) : QObject(parent) {
	if (m_settings.contains(CONVERTION_WAY_KEY)) {
		const char *key = m_settings.value(CONVERTION_WAY_KEY).toByteArray().data();
		m_convertionWay = (ConvertionWay) QMetaEnum::fromType<ConvertionWay>().keyToValue(key);
	} else {
		m_convertionWay = ConverterWizardViewModel::WAV_TO_MP3;
	}

	m_mp3BitrateIndex = m_settings.value(MP3_BITRATE_INDEX_KEY, 8).toInt();
}

ConverterWizardViewModel::~ConverterWizardViewModel()
{
	m_settings.setValue(CONVERTION_WAY_KEY, QMetaEnum::fromType<ConvertionWay>().valueToKey(m_convertionWay));
	m_settings.setValue(MP3_BITRATE_INDEX_KEY, m_mp3BitrateIndex);
}
