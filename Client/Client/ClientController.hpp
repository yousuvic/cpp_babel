#pragma once

#include <iostream>
#include "NetworkData.h"
#include "Protocol.hpp"

#ifdef _WIN32
	#include <winsock2.h>
	#include <Windows.h>
	#include "ClientTCPWin.hpp"
	#include "UDPExchangeWin.hpp"
#else
	#include "ClientTCPLinux.hpp"
	#include "UDPExchangeLinux.hpp"
#endif

#define		PACKET_SIZE	sizeof(t_packet)

class 		ClientController
{
private:
	PacketTypes			typePacket;
	Protocol			*_protocol;
	/*
	**	Win OR Linux
	*/
#ifdef _WIN32
	ClientTCPWin*		_Tcp;
	UDPExchangeWin		srv;
	bool				Caller = false;
#else
	ClientTCPLinux*		_Tcp;
	UDPExchangeLinux	srv;
	bool				Caller;
#endif

public:
	ClientController();
	~ClientController(void);

	void sendActionPackets();
	void update();
};