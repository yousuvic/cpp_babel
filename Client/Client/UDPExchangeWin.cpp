#include	"UDPExchangeWin.hpp"

void		UDPExchangeWin::InitSrvUDP()
{

	slen = sizeof(this->si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((SocketFD = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(SocketFD, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
}

int		UDPExchangeWin::ExchangeSrvUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();

	tv.tv_sec = 10;
	tv.tv_usec = 0;
	//keep listening for data
	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(SocketFD, &readfds);
		FD_SET(SocketFD, &writefds);
		//printf("Waiting for data...");
		//fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		//memset(Packet, '\0', BUFLEN);
		if ((select(SocketFD + 1, &readfds, &writefds, NULL, &tv)) == -1)
		{
			printf("Select error\n");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(SocketFD, &readfds))
		{
			Is_Set = true;
			//try to receive some data, this is a blocking call
			if ((recv_len = recvfrom(SocketFD, (char *)&receivePacket, BUFLEN, 0, (struct sockaddr *)&si_other, &slen)) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			if (receivePacket.Sound != NULL)
			{
				Audio->setReceivedRetenc(receivePacket.Retenc);
				Audio->setReceivedData(receivePacket.Sound);
				receivePacket.Size = 480;
				//std::cout << Audio->getReceivedRetenc() << std::endl;
				/*Audio->setRetenc(Packet.Retenc);
				Packet.Size = 480;
				Audio->setData(Packet.Sound);
				std::cout << Packet.Retenc << std::endl;*/
			}
		}
		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		//printf("Data: %s\n", Packet);
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

					//now reply the client with the same data
					if (sendto(SocketFD, (char *)&sendPacket, BUFLEN, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
					{
						printf("sendto() failed with error code : %d", WSAGetLastError());
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
	closesocket(SocketFD);
	Audio->stop();
	WSACleanup();
	return 0;
}

UDPExchangeWin::UDPExchangeWin()
{
}

UDPExchangeWin::~UDPExchangeWin()
{
}

void		UDPExchangeWin::InitClientUDP()
{
	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket

	if ((ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_otherCli, 0, sizeof(si_otherCli));
	si_otherCli.sin_family = AF_INET;
	si_otherCli.sin_port = htons(PORT);
	si_otherCli.sin_addr.S_un.S_addr = inet_addr(SERVER);
}

int		UDPExchangeWin::ExchangeCliUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();

	tv.tv_sec = 10;
	tv.tv_usec = 0;
	//start communication
	while (1)
	{
		FD_ZERO(&Clientreadfds);
		FD_ZERO(&Clientwritefds);

		FD_SET(ClientSocket, &Clientwritefds);
		FD_SET(ClientSocket, &Clientreadfds);

		//printf("Enter message : ");
		//gets(message);
		//std::cin >> message;
		//send the message
		if ((select(ClientSocket + 1, &Clientreadfds, &Clientwritefds, NULL, &tv)) == -1)
		{
			printf("Select error\n");
			exit(EXIT_FAILURE);
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

				if (sendto(ClientSocket, (char *)&sendPacket, BUFLEN, 0, (struct sockaddr *) &si_otherCli, slenClient) == SOCKET_ERROR)
				{
					printf("sendto() failed with error code : %d", WSAGetLastError());
					exit(EXIT_FAILURE);
				}
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
				if (recvfrom(ClientSocket, (char *)&receivePacket, BUFLEN, 0, (struct sockaddr *)&si_other, &slen) == SOCKET_ERROR)
				{
					printf("recvfrom() failed with error code : %d", WSAGetLastError());
					exit(EXIT_FAILURE);
				}
				if (receivePacket.Sound != NULL)
				{
					Audio->setReceivedRetenc(receivePacket.Retenc);
					Audio->setReceivedData(receivePacket.Sound);
					receivePacket.Size = 480;
					std::cout << "tttttttttttttttttttttt" << std::endl;
					//Audio->setData(Packet.Sound);
					//Audio->setRetenc(Packet.Retenc);
					//Packet.Size = 480;
				}
			}
		}

		//puts(buf);
	}
	closesocket(ClientSocket);
	Audio->stop();
	WSACleanup();
	return 0;
}