#pragma once

#include <stdio.h>
#include "NetworkServices.hpp"
#include "NetworkData.h"
#include "IClientTCP.h"

#define DEFAULT_BUFLEN		480
#define DEFAULT_PORT		"13"
#define	IP_SERVER			"93.31.237.180"

#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientTCPWin	:	public IClientTCP
{
private:
	struct addrinfo *result = NULL;
	struct addrinfo	*ptr = NULL;
	struct addrinfo	hints;

	// for error checking function calls in Winsock library
	int iResult;

	// socket for client to connect to server
	int ConnectSocket;
public:

	ClientTCPWin(void);
	virtual	~ClientTCPWin(void);

	virtual	int		receivePackets(char *);
	virtual	void	socketInit(void);
	virtual	void	socketConnect(char *ip);
	virtual	void	socketUnlock(void);
	virtual int		getConnectSocket() const;
};