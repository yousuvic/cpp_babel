#ifndef CLIENTUDP_HPP
#define	CLIENTUDP_HPP

#include <stdio.h>
#include <iostream>
#include "AudioManager.hpp"
#include "IUDP.hpp"

typedef struct s_Packet
{
	int				Retenc;
	int				Size;
	unsigned char	Sound[480];
}				t_Packet;

#ifdef _WIN32

#include<winsock2.h>

#define BUFLEN sizeof(t_Packet)
#define PORT 4542


//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "10.20.86.176"

class UDPExchange	:	public	IUDP
{
public:
	UDPExchange();
	virtual ~UDPExchange();

	/*
	**	Server
	*/
	virtual	void	InitSrvUDP();
	virtual	int	ExchangeSrvUDP();

	/*
	**	Client
	*/
	virtual	void	InitClientUDP();
	virtual	int	ExchangeCliUDP();

private:
	/*
	**	Server side
	*/
	int					SocketFD;
	struct sockaddr_in	server;
	struct sockaddr_in	si_other;
	int					slen;
	int					recv_len;
	t_Packet			Packet;
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

};

#elif __linux__

#endif // _WIN32

#endif // !CLIENTUDP_HPP
