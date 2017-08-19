#include "converterwizardviewmodel.h"
#include <QMetaEnum>

const QString ConverterWizardViewModel::CONVERTION_WAY_KEY = "wizard/start/convertion";

ConverterWizardViewModel::ConverterWizardViewModel(QObject *parent) : QObject(parent) {
	if (m_settings.contains(CONVERTION_WAY_KEY)) {
		const char *key = m_settings.value(CONVERTION_WAY_KEY).toByteArray().data();
		m_convertionWay = (ConvertionWay) QMetaEnum::fromType<ConvertionWay>().keyToValue(key);
	} else {
		m_convertionWay = ConverterWizardViewModel::WAV_TO_MP3;
	}
}

ConverterWizardViewModel::~ConverterWizardViewModel()
{
	m_settings.setValue(CONVERTION_WAY_KEY, QMetaEnum::fromType<ConvertionWay>().valueToKey(m_convertionWay));
}
