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

#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QThread>
#include <QStringList>

class ConverterThread : public QThread
{
	Q_OBJECT

public:
	enum ConvertionResult { SUCCESS, FAILURE };
	Q_ENUM(ConvertionResult)

	struct ConvertionResultInfo
	{
		ConvertionResultInfo() : result(FAILURE) {}

		ConvertionResultInfo(QString filePath, ConvertionResult result)
		{
			this->filePath = filePath;
			this->result = result;
		}

		QString filePath;
		ConvertionResult result;
	};

	ConverterThread(const QStringList &sourceFilePaths, const QString &destDirPath, QObject *parent = 0) :
		QThread(parent),
		m_sourceFilePaths(sourceFilePaths),
		m_destDirPath(destDirPath)
	{
		qRegisterMetaType<ConvertionResultInfo>("ConvertionResultInfo");
	}

	const QList<ConvertionResultInfo> &convertionResults() const { return m_convertionResults; }

signals:
	void progressChanged(float progress);
	void convertionResultAdded(ConvertionResultInfo convertionResult);

protected:
	QStringList m_sourceFilePaths;
	QString m_destDirPath;
	QList<ConvertionResultInfo> m_convertionResults;

	int m_totalFiles;
	int m_currentFileIndex;
	float m_currentFileProgress;

	float calculateProgress();
};

#endif // CONVERTERTHREAD_H
