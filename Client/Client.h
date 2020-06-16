#ifndef Client_h
#define Client_h
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Definitions.h"

typedef struct {
	UDPsocket socket;
	UDPpacket *packet_in;
	UDPpacket *packet_out;
	IPaddress srvadd;
	char server_ip[100];
    Uint32 lastTimeSent;
	int isHost;
} ClientUDP;

/**
 *  @brief Init client, init SDL_net and connect to server
 *
 *  @param ipadress The ip-adress to connect to
 *  @param isHost If the client is host
 */
ClientUDP client_init_UDP(char *ipadress, int isHost); //Init Client with UDPsocket 

/**
 *  @brief Quits client and clean up mem
 *
 *  @param client The UDP client
 */
int client_quit_UDP(ClientUDP *client); //Quit client UDPsocket

/**
 *  @brief Recv udp packets
 *
 *  @param client The UDP client
 */
int client_recv_UDP(ClientUDP *client); //Receive through UDPsocket

/**
 *  @brief Send udp packets
 *
 *  @param client The UDP client
 */
int client_send_UDP(ClientUDP *client); //Send through UDPsocket
#endif
