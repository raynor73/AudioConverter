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

#ifndef RIFFWRITER_H
#define RIFFWRITER_H

#include <QObject>
#include <QException>

class RiffOutput;

class RiffWriter : public QObject
{
	Q_OBJECT

public:
	class AlreadyHasStateException : QException {};

	static const QString TAG;
	static const QString RIFF_CHUNCK_IDENTIFIER;
	static const QString LIST_CHUNK_IDENTIFIER;

	enum State { IDLE, SEEKING, WRITING_CHUNK, FAILURE };
	Q_ENUM(State)

	RiffWriter(RiffOutput &riffOutput, QObject *parent = 0);

	bool startChunk(const QString &identifier, const QString &subIdentifier = QString());
	bool finishChunk();
	qint64 writeData(const char *data, qint64 maxSize);
	bool seek(qint64 pos);
	qint64 pos() const;

private:
	static const int IDENTIFIER_SIZE = 4;
	static const int LENGTH_FIELD_SIZE = 4;

	State m_state;
	RiffOutput &m_output;

	qint64 m_chunkLengthFieldPosition;
	qint64 m_tailPosition;
	qint64 m_writtenDataSize;

	void changeState(State newState);
};

#endif // RIFFWRITER_H
