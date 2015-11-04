#include <process.h>
#include "AudioManager.hpp"
#include "ClientController.hpp"
#include "UDPExchange.hpp"


void clientLoop(void);

ClientController * client;

void clientLoop()
{
	while (true)
	{
		client->update();
	}
}

int			main()
{
	// initialize the client
	client = new ClientController();

	clientLoop();
	return (0);
}


/*int		main(int ac, char **av)
{
IAudio	*a = new AudioManager;

a->initAudio();
a->start();
a->stop();
delete a;
return (0);
}*/

/*int				main()
{
	UDPExchange	srv;

	srv.InitSrvUDP();
	srv.ExchangeSrvUDP();

	//srv.InitClientUDP();
	//srv.ExchangeCliUDP();
}*/