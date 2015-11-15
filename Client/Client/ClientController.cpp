#include "ClientController.hpp" 

void ClientController::update()
{
	/*Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		//no data recieved
		std::cout << "NO PACKET" << std::endl;
		return;
	}

	int i = 0;
	while (i < data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);
		sendActionPackets();
	}*/
	sendActionPackets();
}

void ClientController::sendActionPackets()
{
	// send action packet
	/*const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);
	t_packet	*PacketFinal;*/

	//memcpy(PacketFinal->encSound, (char *)a->getData().first, MAX_PACKET_SIZE);
	//NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
	//if (strlen((char*)PacketFinal->encSound) == 480)

	//memset(PacketFinal->encSound, 0, MAX_PACKET_SIZE);

	//NetworkServices::sendMessage(network->ConnectSocket, "toto", 4);


	//t_packet	Packet;

	/*if (Audio->getSound() != NULL)
	{
		Packet.retenc = Audio->getRetenc();
		Packet.size = 480;
		memcpy(Packet.encSound, Audio->getSound(), MAX_PACKET_SIZE);
		NetworkServices::sendMessage(_Tcp->getConnectSocket(), &Packet, PACKET_SIZE);
	}*/
	Caller = false;
	if (Caller == true)
	{
		srv.InitSrvUDP();
		srv.ExchangeSrvUDP();
	}
	else
	{
		srv.InitClientUDP();
		srv.ExchangeCliUDP();
	}
}
	

ClientController::ClientController(void)
{
	IClientTCP	*_Tcp = NULL;

	#ifdef WIN32
		_Tcp = new ClientTCPWin();
		std::cout << "* Running in Windows env *" << std::endl;
	#else  //UNIX
		_Tcp = new ClientTCPLinux();
		std::cout << "* Running in UNIX env *" << std::endl;
	#endif


	_Tcp->SocketInit();
	_Tcp->SocketConnect(IP_SERVER);
	_Tcp->socketUnlock();


	// send init packet
	/*const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);*/

	Protocol::Protocol(_Tcp->getConnectSocket());
}

ClientController::~ClientController(void)
{
}