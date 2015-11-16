#ifndef ISOCKET_H
#define	ISOCKET_H

# include <string>

class ISocket
{
public:
	virtual ~ISocket() {}

	virtual	void	socketInit(void) = 0;
	virtual	void	socketConnect(char *ip) = 0;
	virtual	void	socketUnlock(void) = 0;
	virtual	int		receivePackets(char *) = 0;
	virtual int		getConnectSocket() const = 0;
};

#endif // !ISOCKET_H