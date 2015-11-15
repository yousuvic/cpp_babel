#include "NetworkServices.hpp"

int NetworkServices::sendMessage(int curSocket, char *message, int messageSize)
{
	return send(curSocket, message, messageSize, 0);
}

int NetworkServices::receiveMessage(int curSocket, char * buffer, int bufSize)
{
	return recv(curSocket, buffer, bufSize, 0);
}