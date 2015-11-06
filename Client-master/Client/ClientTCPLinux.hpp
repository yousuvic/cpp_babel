#pragma once

#include <stdio.h>
#include "NetworkServices.hpp"
#include "NetworkData.h"
#include "IClientTCP.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define DEFAULT_BUFLEN		480
#define DEFAULT_PORT		"9042"
#define	IP_SERVER			"10.20.86.53"
/*
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
*/
class ClientTCPLinux	:	public IClientTCP
{
private:
	struct addrinfo *result;
	struct addrinfo	*ptr;
	struct addrinfo	hints;

	// for error checking function calls in Winsock library
	int iResult;

	// socket for client to connect to server
	int ConnectSocket;
public:

	ClientTCPLinux(void);
	virtual	~ClientTCPLinux(void);

	virtual	int		receivePackets(char *);
	virtual	void	SocketInit(void);
	virtual	void	SocketConnect(char *ip);
	virtual	void	SocketDeblock(void);
	virtual int		getConnectSocket() const;
};