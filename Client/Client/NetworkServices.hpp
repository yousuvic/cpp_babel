#ifndef NETWORKSERVICES_HPP
#define	NETWORKSERVICES_HPP

#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include "NetworkData.h"

class	NetworkServices
{
public:

	static int sendMessage(int curSocket, t_packet *, int messageSize);
	static int receiveMessage(int curSocket, char * buffer, int bufSize);
};

#endif // !NETWORKSERVICES_HPP
