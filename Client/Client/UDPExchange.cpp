#include	"UDPExchange.hpp"

void		UDPExchange::InitSrvUDP()
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

int		UDPExchange::ExchangeSrvUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();

	//keep listening for data
	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(SocketFD, &readfds);
		FD_SET(SocketFD, &writefds);
		//printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		//memset(Packet, '\0', BUFLEN);

		if ((select(SocketFD + 1, &readfds, &writefds, NULL, NULL)) == -1)
		{
			printf("Select error\n");
			exit(EXIT_FAILURE);
		}
		//if (FD_ISSET(SocketFD, &readfds))
		//{
			Is_Set = true;
			//try to receive some data, this is a blocking call
			if ((recv_len = recvfrom(SocketFD, (char *)&Packet, BUFLEN, 0, (struct sockaddr *)&si_other, &slen)) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			if (Packet.Sound != NULL)
			{
				Audio->setRetenc(Packet.Retenc);
				Packet.Size = 480;
				Audio->setData(Packet.Sound);
				std::cout << Packet.Retenc << std::endl;
			}
		//}
		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		//printf("Data: %s\n", Packet);
		
		/*if (Is_Set == true)
		{
			if (FD_ISSET(SocketFD, &writefds))
			{
				//now reply the client with the same data
				if (sendto(SocketFD, Packet, recv_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
				{
					printf("sendto() failed with error code : %d", WSAGetLastError());
					exit(EXIT_FAILURE);
				}
			}
		}*/
	}
	closesocket(SocketFD);
	WSACleanup();
	return 0;
}

UDPExchange::UDPExchange()
{
}

UDPExchange::~UDPExchange()
{
}

void		UDPExchange::InitClientUDP()
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

int		UDPExchange::ExchangeCliUDP()
{
	IAudio	*Audio = new AudioManager;

	Audio->initAudio();
	Audio->start();
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

		//if (FD_ISSET(ClientSocket, &Clientwritefds))
		//{
			Is_Struct_Set = true;
			if (Audio->getSound() != NULL)
			{
				Packet.Retenc = Audio->getRetenc();
				Packet.Size = 480;
				memcpy(Packet.Sound, Audio->getSound(), 480);
				std::cout << Packet.Retenc << std::endl;
			}
			if (sendto(ClientSocket, (char *)&Packet, BUFLEN, 0, (struct sockaddr *) &si_otherCli, slenClient) == SOCKET_ERROR)
			{
				printf("sendto() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
		//}
		

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		//memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		/*if (Is_Struct_Set == true)
		{
			if (FD_ISSET(ClientSocket, &Clientreadfds))
			{
				if (recvfrom(ClientSocket, buf, BUFLEN, 0, (struct sockaddr *) &si_otherCli, &slenClient) == SOCKET_ERROR)
				{
					printf("recvfrom() failed with error code : %d", WSAGetLastError());
					exit(EXIT_FAILURE);
				}
			}
		}
		
		puts(buf);*/
	}
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}