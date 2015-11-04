#ifndef CLIENTCONTROLLER_HPP
#define	CLIENTCONTROLLER_HPP

#include <iostream>
#include "ClientTCP.hpp"
#include "NetworkData.h"
#include "UDPExchange.hpp"

#ifdef _WIN32

#include <winsock2.h>
#include <Windows.h>

#endif // _WIN32

#define	PACKET_SIZE	sizeof(t_packet)

class ClientController
{
private:
	ClientTCP*		_Tcp;
	UDPExchange		srv;
public:
	ClientController();
	~ClientController(void);

	void sendActionPackets();
	void update();
};

#endif // !ClientController_HPP
