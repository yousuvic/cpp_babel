#pragma once

#include <string>

class IUDPExchange
{
public:
	virtual	int 	InitSrvUDP() = 0;
	virtual	int 	ExchangeSrvUDP() = 0;
	virtual	int 	InitClientUDP() = 0;
	virtual	int		ExchangeCliUDP() = 0;
};