#include "Protocol.hpp"

void	Protocol::requestAuth()
{
	NetworkServices::sendMessage(_socket, Salut, strlen(Salut));
}

int		Protocol::signUp(std::string username, std::string password)
{
	std::string		identificationSecret;

	identificationSecret = "signUp;" + username + ";" + password;
	NetworkServices::sendMessage(_socket, (char *)identificationSecret.c_str(), strlen(identificationSecret.c_str()));
	NetworkServices::receiveMessage(_socket, _err, 2);
	if (strcmp(_err, InvalidUsername) == 0)
		return(01);
	else if (strcmp(_err, InvalidPassword) == 0)
		return(02);
	else if (strcmp(_err, UnvalableUsername) == 0)
		return(03);
	return(0);
}

int		Protocol::sigIn(std::string username, std::string password)
{
	std::string		identificationSecret;

	identificationSecret = "sigIn;" + username + ";" + password;
	NetworkServices::sendMessage(_socket, (char *)identificationSecret.c_str(), strlen(identificationSecret.c_str()));
	NetworkServices::receiveMessage(_socket, _err, 2);
	if (strcmp(_err, UnknowUser) == 0)
		return(04);
	return(0);
}

int		Protocol::freindRequest(int action, std::string userEmittingRequest)
{	
	std::string  wAction;

	if (action == 0)
		wAction = "friendRequest;0;"+ userEmittingRequest;
	else if (action == 1)
		wAction = "friendRequest;1;" + userEmittingRequest;
	NetworkServices::sendMessage(_socket, (char *)wAction.c_str(), strlen(wAction.c_str()));
	NetworkServices::receiveMessage(_socket, _err, 2);
	if (strcmp(_err, UnknowUser) == 0)
		return(04);
	else if (strcmp(_err, AlreadyFriend) == 0)
		return(05);
	else if (strcmp(_err, NotFriend) == 0)
		return(06);
	return(0);
}

int		Protocol::freindValidation(bool action, std::string username)
{
	std::string  wAction;

	if (action == true)
		wAction = "friendValidation;true;" + username;
	else if (action == false)
		wAction = "friendValidation;false;" + username;
	NetworkServices::sendMessage(_socket, (char *)wAction.c_str(), strlen(wAction.c_str()));
	NetworkServices::receiveMessage(_socket, _err, 2);
	if (strcmp(_err, AlreadyFriend) == 0)
		return(05);
	else if (strcmp(_err, UnknowUser) == 0)
		return(04);
	return(0);
}

int		Protocol::checkStatus(std::string friendUsername)
{
	NetworkServices::sendMessage(_socket, (char *)friendUsername.c_str(), strlen(friendUsername.c_str()));
	NetworkServices::receiveMessage(_socket, _err, 2);
	if (strcmp(_err, UnknowUser) == 0)
		return(04);
	if (strcmp(_err, UserOffline) == 0)
		return(07);
	return(0);
}

void	Protocol::sendIp(std::string friendUsername, std::string ip, int port)
{
	(void)port;
	NetworkServices::sendMessage(_socket, (char *)ip.c_str(), strlen(ip.c_str()));
}

void	Protocol::answerCall(std::string friendUsername, std::string status)
{

}

Protocol::Protocol(int socket) : _socket(socket)
{
}

Protocol::~Protocol()
{
}