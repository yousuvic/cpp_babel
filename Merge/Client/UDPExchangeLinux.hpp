#pragma once

#include <stdio.h>
#include <iostream>
#include "AudioManager.hpp"
#include "IUDPExchange.hpp"

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include 	<netdb.h>

typedef struct s_Packet
{
	int				Retenc;
	int				Size;
	unsigned char	Sound[480];
}				t_Packet;

#define BUFLEN 		sizeof(t_Packet)
#define PORT 		"4542"

#define SERVER 		"127.0.0.1"

class UDPExchangeLinux : public IUDPExchange
{
public:
	UDPExchangeLinux();
	~UDPExchangeLinux();

	virtual void	InitSrvUDP();
	virtual int		ExchangeSrvUDP();

	virtual void	InitClientUDP();
	virtual int		ExchangeCliUDP();

private:
	/*
	**	Server side
	*/
	int					SocketFD;
	struct addrinfo		hints;
	struct addrinfo		*servinfo;
	struct sockaddr_in	clientAddress;
	socklen_t			clientAddressLength;
	int					slen;
	int					recv_len;
	t_Packet			sendPacket;
	t_Packet			receivePacket;

	/*
	**	Select Srv
	*/
	fd_set	readfds;
	fd_set	writefds;
	bool	Is_Set;

	/*
	**	Client side
	*/
	struct sockaddr_in	si_otherCli;
	int					ClientSocket;
	int					slenClient;
//	WSADATA				WsaData;

	/*
	**	Select Client
	*/
	fd_set	Clientreadfds;
	fd_set	Clientwritefds;
	bool	Is_Struct_Set;
	struct timeval			tv;

};