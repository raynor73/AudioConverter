#ifndef RESAMPLER_H
#define RESAMPLER_H

#include <QObject>

class Resampler : public QObject
{
	Q_OBJECT

public:
	explicit Resampler(QObject *parent = 0);

};

#endif // RESAMPLER_H
