#include "Protocol.hpp"

void	Protocol::requestAuth()
{

}

void	Protocol::signUp(std::string, std::string)
{

}

void	Protocol::sigIn(std::string, std::string)
{

}

void	Protocol::friendRequest(int action, std::string userEmittingRequest)
{

}

void	Protocol::friendValidation(bool action, std::string username)
{

}

void	Protocol::checkStatus(std::string friendUsername, std::string status)
{

}

void	Protocol::sendIp(std::string friendUsername, std::string ip, int port)
{

}

void	Protocol::answerCall(std::string friendUsername, std::string status)
{

}

Protocol::Protocol(int socket) : _Socket(socket)
{
}

Protocol::~Protocol()
{
}