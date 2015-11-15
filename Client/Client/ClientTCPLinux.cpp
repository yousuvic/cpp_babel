#ifdef _WIN32
#else

#include "ClientTCPLinux.hpp"
#include <iostream>

int		ClientTCPLinux::receivePackets(char *recvbuf)
{
	iResult = NetworkServices::receiveMessage(ConnectSocket, recvbuf, MAX_PACKET_SIZE);

	if (iResult == 0)
	{
		std::cout << "Connection closed\n" << std::endl;
		close(ConnectSocket);
		return 1;
	}
	return iResult;
}

void	ClientTCPLinux::SocketInit(void)
{
	std::cout << "Init Client TCP...\n" << std::endl;
}

void	ClientTCPLinux::SocketConnect(char *ip)
{
	if((ConnectSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "socket failed\n" << std::endl;
		exit(1);
	}

	memset(&serveraddr, 0x00, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(DEFAULT_PORT);
 	
 	if((serveraddr.sin_addr.s_addr = inet_addr(IP_SERVER)) == (unsigned long)INADDR_NONE)
	{
		hostp = gethostbyname(IP_SERVER);
		if(hostp == (struct hostent *)NULL)
		{
			std::cerr << "host not found\n" << std::endl;
			close(ConnectSocket);
			exit(-1);
		}
		memcpy(&serveraddr.sin_addr, hostp->h_addr, sizeof(serveraddr.sin_addr));
	}


	if((connect(ConnectSocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)
	{
		std::cerr << "connect failed\n" << std::endl;
		close(ConnectSocket);
		exit(-1);
	}
	else
		std::cout << "Connection established...\n" << std::endl;
}

void	ClientTCPLinux::socketUnlock(void)
{
}

ClientTCPLinux::ClientTCPLinux(void)
{
}

ClientTCPLinux::~ClientTCPLinux()
{
}

int		ClientTCPLinux::getConnectSocket() const
{
	return ConnectSocket;
}

#endif