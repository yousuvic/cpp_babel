#include "Client_Core/ClientController.hpp"

#ifdef _WIN32
#include <process.h>
#include "Client_Core/UDPExchangeWin.hpp"
#else
#include "Client_Core/UDPExchangeLinux.hpp"
#endif

#include "babelgui.h"
#include "connectionwidget.h"
#include <QtWidgets/QApplication>

//void clientLoop(void);

//ClientController * client;

/*void clientLoop()
{
	while (true)
	{
		client->update();
	}
}*/

/*int			main()
{
	// initialize the client
	client = new ClientController();

	clientLoop();
	return (0);
}*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	babelGUI b;
	connectionWidget w;


	w.show();
	return a.exec();
}