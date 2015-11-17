#include "worker.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>
#include "Client_Core/ClientController.hpp"

//ClientController * client;

/*void clientLoop()
{
	while (true)
	{
		client->update();
	}
}*/

void	Worker::run()
{
	//client = new ClientController();
	mutex.lock();
	qDebug() << "toto";
	//clientLoop();
	mutex.unlock();
}

Worker::Worker(QObject *parent) :
QObject(parent)
{
	_working = false;
	_abort = false;

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(run()));
	timer->start(100);
}

Worker::~Worker()
{
}