#pragma once

#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include "AudioManager.hpp"
#include "IUDPExchange.hpp"

typedef struct s_Packet
{
	int				Retenc;
	int				Size;
	unsigned char	Sound[480];
}				t_Packet;

#define BUFLEN 		sizeof(t_Packet)
#define PORT 		4542

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER 		"10.20.86.176"

class UDPExchangeWin : IUDPExchange
{
public:
	UDPExchangeWin();
	virtual ~UDPExchangeWin();

	virtual void	InitSrvUDP();
	virtual int		ExchangeSrvUDP();

	virtual void	InitClientUDP();
	virtual int		ExchangeCliUDP();

private:

	/*
	**	Server side
	*/
	int					SocketFD;
	struct sockaddr_in	server;
	struct sockaddr_in	si_other;
	int					slen;
	int					recv_len;
	t_Packet			sendPacket;
	t_Packet			receivePacket;
	WSADATA				wsa;

	/*
	**	Select Srv
	*/
	fd_set	readfds;
	fd_set	writefds;
	bool	Is_Set = false;

	/*
	**	Client side
	*/
	struct sockaddr_in	si_otherCli;
	int					ClientSocket;
	int					slenClient = sizeof(si_other);
	WSADATA				WsaData;

	/*
	**	Select Srv
	*/
	fd_set	Clientreadfds;
	fd_set	Clientwritefds;
	bool	Is_Struct_Set = false;
	struct timeval			tv;

};