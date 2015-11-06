#pragma once

#include <string>

class IUDPExchange
{
public:
	virtual	void	InitSrvUDP() = 0;
	virtual	int 	ExchangeSrvUDP() = 0;

	virtual	void	InitClientUDP() = 0;
	virtual	int		ExchangeCliUDP() = 0;
};