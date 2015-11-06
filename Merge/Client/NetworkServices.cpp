#include "NetworkServices.hpp"

int NetworkServices::sendMessage(int curSocket, t_packet *packet, int messageSize)
{
	return send(curSocket, (char *)packet, messageSize, 0);
}

int NetworkServices::receiveMessage(int curSocket, char * buffer, int bufSize)
{
	return recv(curSocket, buffer, bufSize, 0);
}

