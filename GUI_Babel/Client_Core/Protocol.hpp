#ifndef PROTOCOL_HPP
#define	PROTOCOL_HPP

#include <iostream>
#include <string>
#include <list>
#include "ErrorCodes.h"
#include "NetworkServices.hpp"

class Protocol
{
public:
	Protocol(int socket);
	~Protocol();

	/*
	**	Client	-->	Server
	*/
	void	requestAuth();
	int		signUp(std::string, std::string);
	int		sigIn(std::string, std::string);
	int		freindRequest(int action, std::string userEmittingRequest);
	int		freindValidation(bool action, std::string username);
	int		checkStatus(std::string friendUsername);
	void	sendIp(std::string friendUsername, std::string ip, int port);
	void	answerCall(std::string friendUsername, std::string status);

	/*
	**	Server	-->	Client
	*/
	void	getdUserByUsername(std::string);
	void	freindStatusChanged(std::string friendUsername, std::string status);

	/*
	**	P2P
	*/
	void	welcome();
	void	callClient(std::string ip, int port);
	void	sendText(int UserID, std::string message);

private:
	int		_socket;
	char	_err[2];
};

#endif // !PROTOCOL_HPP
