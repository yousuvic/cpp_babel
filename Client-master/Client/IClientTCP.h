#pragma once

#include <string>

class IClientTCP
{
public:
	virtual ~IClientTCP() {}

	virtual	void	SocketInit(void) = 0;
	virtual	void	SocketConnect(char *ip) = 0;
	virtual	void	socketUnlock(void) = 0;
	virtual	int		receivePackets(char *) = 0;
	virtual int		getConnectSocket() const = 0;
};