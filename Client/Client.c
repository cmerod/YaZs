#include "Client.h"
#pragma warning(disable : 4996)

ClientUDP client_init_UDP(char *ipadress, int isHost)
{
	ClientUDP client;
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(-1);
	}

	/* Open a socket on random port */
	if (!(client.socket = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(-1);
	}

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&client.srvadd, ipadress, SERVER_PORT) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-1);
	}

	/* Allocate memory for the packet */
	if (!(client.packet_in = SDLNet_AllocPacket(1500)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	client.packet_in->len = 0;
    
	/* Allocate memory for the packet */
	if (!(client.packet_out = SDLNet_AllocPacket(1500)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	client.isHost = isHost;
    client.lastTimeSent = 0;
	return client;
}

int client_quit_UDP(ClientUDP *client)
{
    SDLNet_FreePacket(client->packet_out);
	SDLNet_FreePacket(client->packet_in);
	SDLNet_Quit();
	return 0;
}

int client_recv_UDP(ClientUDP *client)
{
	/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
    return SDLNet_UDP_Recv(client->socket, client->packet_in);
}

int client_send_UDP(ClientUDP *client)
{
	if (strlen((char *)client->packet_out->data) > 0)
	{
		client->packet_out->address.host = client->srvadd.host;//srvadd.host;	/* Set the destination host */
		client->packet_out->address.port = client->srvadd.port;//srvadd.port;	/* And destination port */

		client->packet_out->len = (int)strlen((char *)client->packet_out->data) + 1;
        
		SDLNet_UDP_Send(client->socket, -1, client->packet_out); /* This sets the p->channel */
		strcpy((char*)client->packet_out->data, "");
        client->lastTimeSent = 0;
        client->lastTimeSent = SDL_GetTicks();
	}
	return 0;
}
