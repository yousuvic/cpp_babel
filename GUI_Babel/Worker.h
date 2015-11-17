#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>


class Worker : public QObject
{
	Q_OBJECT

public:
	explicit	Worker(QObject *parent = 0);
	~Worker();

public slots:
	void		run();

private:
	bool _abort;
	bool _working;
	QMutex mutex;


signals:
	void workRequested();
	void valueChanged(const QString &value);
	void finished();
};

#endif // WORKER_H