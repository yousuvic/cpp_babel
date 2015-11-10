#ifndef NETWORKDATA_H
#define	NETWORKDATA_H

#include <string.h>

#define MAX_PACKET_SIZE 480

enum PacketTypes 
{

	INIT_CONNECTION = 0,
	ACTION_EVENT = 1,

};

typedef	struct	s_packet
{
	int				retenc;
	int				size;
	unsigned char	encSound[480];
}				t_packet;

struct Packet 
{

	unsigned int packet_type;

	void serialize(char * data) 
	{
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) 
	{
		memcpy(this, data, sizeof(Packet));
		printf("%s\n", data);
		memset(data, 0, strlen(data));
	}
};

#endif // !NETWORKDATA_H