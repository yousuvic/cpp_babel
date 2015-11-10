#ifdef _WIN32
#else

#include	"UDPExchangeLinux.hpp"

void		UDPExchangeLinux::InitSrvUDP()
{
	clientAddressLength = sizeof clientAddress;
	slen = sizeof(this->servinfo);
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
 	hints.ai_flags = AI_PASSIVE;  
	if ((getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
	{
		std::cout << "getaddrinfo failed\n" << std::endl;
		exit(-1);
	}
	if ((SocketFD = socket(servinfo->ai_family, servinfo->ai_socktype,
                        	servinfo->ai_protocol)) == -1)
	{
		std::cout << "socket failed\n" << std::endl;
		exit(-1);
	}
	if (bind(SocketFD, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
    	close(SocketFD);
		std::cout << "bind failed\n" << std::endl;
		exit(-1);
	}
  	freeaddrinfo(servinfo);
  	std::cout << "Init Server UDP : done.\n" << std::endl;
}

int 		UDPExchangeLinux::ExchangeSrvUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(SocketFD, &readfds);
		FD_SET(SocketFD, &writefds);
		//fflush(stdout);

		if ((select(SocketFD + 1, &readfds, &writefds, NULL, NULL)) == -1)
		{
			std::cout << "select failed\n" << std::endl;
			return 1;
		}

		if (FD_ISSET(SocketFD, &readfds))
		{
			Is_Set = true;
  			if (recvfrom(SocketFD, (char *)&receivePacket, BUFLEN, 0,
                	 (struct sockaddr *) &clientAddress,
            	     &clientAddressLength) == -1)
  			{
  				std::cout << "recvfrom failed\n" << std::endl;
  				return 1;
  			}

			if ((char *)receivePacket.Sound != NULL)
			{
				Audio->setRetenc(receivePacket.Retenc);
				Audio->setData(receivePacket.Sound);
				receivePacket.Size = 480;
				//std::cout << receivePacket.Retenc << std::endl;
			}
		}
		if (Is_Set == true)
		{
			if (FD_ISSET(SocketFD, &writefds))
			{
				if (Audio->getData() != NULL)
				{
					sendPacket.Retenc = Audio->getRetenc();
					sendPacket.Size = 480;
					memcpy(sendPacket.Sound, Audio->getData(), 480);
					std::cout << sendPacket.Retenc << std::endl;
				}
				//now reply the client with the same data
				std::cout << "ici2" << std::endl;
				//std::cout << sendPacket.Sound << std::endl;
				if (sendto(SocketFD, (char *)&sendPacket, BUFLEN, 0,
					servinfo->ai_addr, servinfo->ai_addrlen) == -1)
				{
					std::cerr << "sendto failed\n" << std::endl;
					return 1;
				}
			}
		}
	}
	close(SocketFD);
	Audio->stop();
	return 0;
}

UDPExchangeLinux::UDPExchangeLinux() : 	Is_Set(false),
										slenClient(sizeof(servinfo)),
										Is_Struct_Set(false)
{
}

UDPExchangeLinux::~UDPExchangeLinux()
{
}

void		UDPExchangeLinux::InitClientUDP()
{
	memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_INET;
  	hints.ai_socktype = SOCK_DGRAM;

	if ((getaddrinfo(SERVER, PORT, &hints, &servinfo)) != 0)
	{
    	std::cout << "getaddrinfo failed\n" << std::endl;
		exit(-1);
  	}
  	if ((ClientSocket = socket(servinfo->ai_family, servinfo->ai_socktype,
                              	servinfo->ai_protocol)) == -1)
  	{
    	std::cout << "socket failed\n" << std::endl;
		exit(-1);
  	}

	//memset((char *)&si_otherCli, 0, sizeof(si_otherCli));
	//si_otherCli.sin_family = AF_INET;
	//si_otherCli.sin_port = htons(PORT);
	//si_otherCli.sin_addr.S_un.S_addr = inet_addr(SERVER);
	std::cout << "Init Client UDP : done.\n" << std::endl;
}

int		UDPExchangeLinux::ExchangeCliUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&Clientreadfds);
		FD_ZERO(&Clientwritefds);

		FD_SET(ClientSocket, &Clientwritefds);
		FD_SET(ClientSocket, &Clientreadfds);

		if ((select(ClientSocket + 1, &Clientreadfds, &Clientwritefds, NULL, &tv)) == -1)
		{
			std::cerr << "select failed\n" << std::endl;
			return 1;
		}

		if (FD_ISSET(ClientSocket, &Clientwritefds))
		{
			if (Audio->getData() != NULL)
			{
				Is_Struct_Set = true;
				sendPacket.Retenc = Audio->getRetenc();
				sendPacket.Size = 480;
				memcpy(sendPacket.Sound, Audio->getData(), 480);
				//std::cout << Packet.Retenc << std::endl;
			}
			if (sendto(ClientSocket, (char *)&sendPacket, BUFLEN, 0, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
			{
				std::cerr << "sendto() failed\n" << std::endl;
				return 1;
			}
		}
		
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		//memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (Is_Struct_Set == true)
		{
			if (FD_ISSET(ClientSocket, &Clientreadfds))
			{
			if (recvfrom(ClientSocket, (char *)&receivePacket, BUFLEN, 0,
                	 (struct sockaddr *) &clientAddress,
            	     &clientAddressLength) == -1)
				{
					std::cerr << "recvfrom() failed\n" << std::endl;
					return 1;
				}
				if ((char *)receivePacket.Sound != NULL)
				{
					Audio->setReceivedRetenc(receivePacket.Retenc);
					Audio->setReceivedData(receivePacket.Sound);
					receivePacket.Size = 480;
					std::cout << "receivePacket ici" << std::endl;
					//std::cout << rPacket.Retenc << std::endl;
					//Audio->setData(Packet.Sound);
					//Audio->setRetenc(Packet.Retenc);
					//Packet.Size = 480;
				}
			}
		}
	}
	close(ClientSocket);
	Audio->stop();
	std::cout << "ici3" << std::endl;
	return 0;
}

#endif