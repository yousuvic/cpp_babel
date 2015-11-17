#include "worker.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>
#include "Client_Core/ClientController.hpp"

ClientController * client;

void clientLoop()
{
	while (true)
	{
		client->update();
	}
}

void	Worker::run()
{
	mutex.lock();
	client = new ClientController();
	clientLoop();
	mutex.unlock();
}

Worker::Worker(QObject *parent) :
QObject(parent)
{
	_working = false;
	_abort = false;
}

Worker::~Worker()
{
}