#pragma once

#ifdef _WIN32
	#include <winsock2.h>
	#include <Windows.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
#endif

#include <iostream>
#include <string>
#include "NetworkData.h"

class	NetworkServices
{
public:
	static int sendMessage(int curSocket, t_packet *, int messageSize);
	static int receiveMessage(int curSocket, char * buffer, int bufSize);
};