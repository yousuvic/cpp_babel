#include "AudioManager.hpp"
#include "ClientController.hpp"

#ifdef _WIN32
	#include <process.h>
	#include "UDPExchangeWin.hpp"
#else
	#include "UDPExchangeLinux.hpp"
#endif

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

/*int					main()
{
	IUDPExchange	*serv = NULL;

	#ifdef WIN32
		serv = new UDPExchangeWin();
		std::cout << "* Running in Windows env *" << std::endl;
	#else  //UNIX
		serv = new UDPExchangeLinux();
		std::cout << "* Running in UNIX env *" << std::endl;
	#endif

	serv->InitSrvUDP();
	serv->ExchangeSrvUDP();

	//serv->InitClientUDP();
	//serv->ExchangeCliUDP();
}*/