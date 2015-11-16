#pragma once

#include <string>

class IClientTCP
{
public:
	virtual ~IClientTCP() {}

	virtual	void	socketInit(void) = 0;
	virtual	void	socketConnect(char *ip) = 0;
	virtual	void	socketUnlock(void) = 0;
	virtual	int		receivePackets(char *) = 0;
	virtual int		getConnectSocket() const = 0;
};