#ifndef CLIENTTCP_HPP
#define	CLIENTTCP_HPP

#include <stdio.h>
#include "NetworkServices.hpp"
#include "NetworkData.h"
#include "ISocket.h"

// size of our buffer
#define DEFAULT_BUFLEN 480
// port to connect sockets through 
#define DEFAULT_PORT "9042"
#define	IP_SERVER	"10.20.86.53"

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientTCP	:	public ISocket
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

	// ctor/dtor
	ClientTCP(void);
	virtual	~ClientTCP(void);

	virtual	int		receivePackets(char *);
	virtual	void	socketInit(void);
	virtual	void	socketConnect(char *ip);
	virtual	void	socketUnlock(void);
	virtual int		getConnectSocket() const;
};

#elif __linux__


#else
#error Platform not supported
#endif // !_WIN32


#endif // !CLIENTTCP_HPP
