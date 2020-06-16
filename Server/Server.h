#ifndef Server_h
#define Server_h

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
#include "Avatar.h"
#include "World.h"
#include "TimeManager.h"
#include "../Client/Definitions.h"

#define MAX_SOCKETS 4
#define SERVER_PORT 8888
#define MAX_DISCONNECT_TIME 20000

typedef struct {
	bool in_use;
	char text[1000];
    char client_data[10000];
    int channel_id;
	IPaddress client_address;
    Uint32 lastTimeRecived;
} Client;

typedef struct {
	int num_clients;
	bool running;
	struct {
		int length;
		char msg[1000];
	} client_msg;
	Client clients[MAX_SOCKETS];
	UDPsocket socket;
	UDPpacket *packet_in;
	UDPpacket *packet_out;
    Timer timer;
	Uint32 startTime;
    int currentState;
} ServerUDP;


/**
*  @brief This initializes the server and prepares it to send and receive from a UDPsocket. Also starts a timer.
*
*/
ServerUDP server_init_UDP(void);

/**
*  @brief Shuts down the UDPsocket and closes the server. 
*
*/
int server_quit_UDP(ServerUDP *server);

/**
*  @brief Functions that deal with anything related to incoming packets
*
*/
void server_recv(ServerUDP *server, World *world);


/**
 *  @brief Checks if the client connected is a new client. Returns 1 if server->packet_in->channel = -1
 *  otherwise 0
 *
 *  @param server The server UDP struct.
 *  @todo Should come up with a better name...
 */
int server_connection_is_new(ServerUDP server);

/**
 *  @brief Checks how many clients are connected, will return 0 if limit has been reached, otherwise 1. Will return -1 on error
 *
 *  @param server The server UDP struct.
 *  @todo Implement a way to send a error msg to connecting client if limit has been reached
 *  @todo Do error checking
 */
int server_allows_new_clients(ServerUDP server);

/**
 *  @brief Add the string to the outgoing msg queue
 *
 *  @param server The server UDP struct.
 *  @param cmd The command we want to send to the client
 */
void server_add_outgoing_command(ServerUDP *server, char *cmd);

/**
*  @brief Bind an address to a UDPsocket channel, saves address into server.clients[i].client_address
*
*/
int server_bind_adress_UDP(ServerUDP *server);

/**
*  @brief Takes received data from clients and changes client input arrays
*
*  @param packet_in The packet received from a client
 * @param input A matrix of inputs from the different clients. Each client has their own input array and a space represents a key
*/
int server_handle_client_input(UDPpacket *packet_in, bool input[MAX_PLAYERS][NUM_OF_KEYS]);

/**
*  @brief Here updates to the gamestate are made. Moving objects, collision detection, attacks, generate/remove enemies, determine win/loss
*
*/
void server_update(ServerUDP *server, World *world);

/**
*  @brief First checks for any zombie connections and removes them. Then prepares the packet to be sent to clients and lastly sends the packet.
*
*  @param server Contains the UDPsocket and UDPpackets to be used. Also stores client data
*  @param world Contains object structs that will be converted and stored as string in the UDPpacket
*/
void server_send(ServerUDP *server, World *world);

/**
*  @brief Changes the game state
*
*  @param world Contains player input and game data
*  @param server Contains timer, currentstate, startTime and clients
*/
void server_game_state(World *world, ServerUDP *server);
#endif


