#ifndef PROTOCOL_HPP
#define	PROTOCOL_HPP

#include <string>
#include <list>
#include "ErrorCodes.h"

class Protocol
{
public:
	Protocol();
	~Protocol();

	/*
	**	Client	-->	Server
	*/
	void	requestAuth();
	void	signUp(std::string, std::string);
	void	sigIn(std::string, std::string);
	void	friendRequest(int action, std::string userEmittingRequest);
	void	friendValidation(bool action, std::string username);
	void	checkStatus(std::string friendUsername, std::string status);
	void	sendIp(std::string friendUsername, std::string ip, int port);
	void	answerCall(std::string friendUsername, std::string status);

	/*
	**	Server	-->	Client
	*/
	void	getdUserByUsername(std::string);
	void	friendStatusChanged(std::string friendUsername, std::string status);

	/*
	**	P2P
	*/
	void	welcome();
	void	callClient(std::string ip, int port);
	void	sendText(int UserID, std::string message);

private:
	int		_Socket;
};

#endif // !PROTOCOL_HPP
