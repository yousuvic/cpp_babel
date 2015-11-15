#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include "NetworkServices.hpp"
#include "NetworkData.h"
#include "IClientTCP.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_BUFLEN		480
#define DEFAULT_PORT		4242
#define	IP_SERVER 			"127.0.0.1"

class ClientTCPLinux	:	public IClientTCP
{
private:

	struct hostent		*hostp;
	struct sockaddr_in 	serveraddr;

	int iResult;
	int ConnectSocket;

public:

	ClientTCPLinux(void);
	virtual	~ClientTCPLinux(void);

	virtual	int		receivePackets(char *);
	virtual	void	SocketInit(void);
	virtual	void	SocketConnect(char *ip);
	virtual	void	socketUnlock(void);
	virtual int		getConnectSocket() const;
};