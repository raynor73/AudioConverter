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

#include "converterwizardviewmodel.h"
#include <QMetaEnum>

const QString ConverterWizardViewModel::CONVERTION_WAY_KEY = "wizard/start/convertion";
const QString ConverterWizardViewModel::MP3_BITRATE_INDEX_KEY = "wizard/mp3/bitrate_index";
const QString ConverterWizardViewModel::SOURCE_DIR_PATH_KEY = "wizard/files/source_dir_path";
const QString ConverterWizardViewModel::DEST_DIR_PATH_KEY = "wizard/files/dest_dir_path";
const QString ConverterWizardViewModel::WAV_SAMPLE_RATE_INDEX_KEY = "wizard/wav/sample_rate";
const QString ConverterWizardViewModel::WAV_BITS_PER_SAMPLE_INDEX_KEY = "wizard/wav/bits_per_sample";

QList<QString> ConverterWizardViewModel::m_mp3BitrateNames = {
	"32", "40", "48", "56", "64", "80", "96", "112", "128", "160", "192", "224", "256", "320"
};
QList<int> ConverterWizardViewModel::m_mp3BitrateValues = {
	32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320
};

QStringList ConverterWizardViewModel::m_wavSampleRateNames = {
	"48000", "47250", "44100", "44056", "37800", "32000", "22050", "16000", "11025", "8000"
};
QList<int> ConverterWizardViewModel::m_wavSampleRateValues = {
	48000, 47250, 44100, 44056, 37800, 32000, 22050, 16000, 11025, 8000
};
QStringList ConverterWizardViewModel::m_wavBitsPerSampleNames = {
	"24", "16", "8"
};
QList<int> ConverterWizardViewModel::m_wavBitsPerSampleValues = {
	24, 16, 8
};

ConverterWizardViewModel::ConverterWizardViewModel(QSettings &settings, QObject *parent) :
	QObject(parent),
	m_settings(settings)
{
	if (m_settings.contains(CONVERTION_WAY_KEY)) {
		const char *key = m_settings.value(CONVERTION_WAY_KEY).toByteArray().data();
		m_convertionWay = (ConvertionWay) QMetaEnum::fromType<ConvertionWay>().keyToValue(key);
	} else {
		m_convertionWay = ConverterWizardViewModel::WAV_TO_MP3;
	}

	m_mp3BitrateIndex = m_settings.value(MP3_BITRATE_INDEX_KEY, 8).toInt();

	m_wavSampleRateIndex = m_settings.value(WAV_SAMPLE_RATE_INDEX_KEY, 2).toInt();
	m_wavBitsPerSampleIndex = m_settings.value(WAV_BITS_PER_SAMPLE_INDEX_KEY, 1).toInt();

	m_sourceDirPath = m_settings.value(SOURCE_DIR_PATH_KEY, "").toString();
	m_destDirPath = m_settings.value(DEST_DIR_PATH_KEY, "").toString();
}

ConverterWizardViewModel::~ConverterWizardViewModel()
{
	m_settings.setValue(CONVERTION_WAY_KEY, QMetaEnum::fromType<ConvertionWay>().valueToKey(m_convertionWay));

	m_settings.setValue(MP3_BITRATE_INDEX_KEY, m_mp3BitrateIndex);

	m_settings.setValue(WAV_SAMPLE_RATE_INDEX_KEY, m_wavSampleRateIndex);
	m_settings.setValue(WAV_BITS_PER_SAMPLE_INDEX_KEY, m_wavBitsPerSampleIndex);

	if (!m_sourceDirPath.isEmpty())
		m_settings.setValue(SOURCE_DIR_PATH_KEY, m_sourceDirPath);
	if (!m_destDirPath.isEmpty())
		m_settings.setValue(DEST_DIR_PATH_KEY, m_destDirPath);
}
