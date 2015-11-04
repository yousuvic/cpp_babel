#ifndef IUDP_HPP
#define	IUDP_HPP

# include <string>

class		IUDP
{
public:
	virtual ~IUDP() {}

	/*
	**	Server
	*/
	virtual	void	InitSrvUDP() = 0;
	virtual	int		ExchangeSrvUDP() = 0;

	/*
	**	Client
	*/
	virtual	void	InitClientUDP() = 0;
	virtual	int		ExchangeCliUDP() = 0;
};

#endif // !IUDP_HPP