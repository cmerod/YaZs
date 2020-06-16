#ifndef UDP_h
#define UDP_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif
#include "Server.h"

/**
 *  @brief Send a udp packet to a singel client
 *  Returns -1 on error.
 *
 *  @param server The server UDP struct, any in data will be placed in server.*packet_in
 */
int udp_send_singel_client(ServerUDP *server, int channel_id);
/**
*  @brief Checks if there is a new UDP packet. Returns 1 if there is otherwise returns 0.
*  Returns -1 on error.
*
*  @param server The server UDP struct, any in data will be placed in server.*packet_in
*/
int udp_recv(ServerUDP *server);

/**
*  @brief Sends a udp packet through all channels in a udpsocket that has bound ipaddresses.
*
*/
int udp_send(ServerUDP *server);

/**
*  @brief Takes the various object structs and converts them to string format and pushes them into a UDPpacket.
*  
*  @param server Contains the UDPpacket that will recieve the strings
*  @param world Contains the object structs that will be converted
*/
int udp_make_packet(ServerUDP *server, World *world);

/**
*  @brief Takes avatar object and converts it into string format
*
*/
void udp_convert_struct(char *packetOutData, Avatar temp_avatar);

/**
*  @brief Unbinds a client from a channel on the UDPsocket
*
*  @param server The struct that contains the client
*  @param channel_id The channel that gets any bound addresses unbound
*/
int udp_unbind_address(ServerUDP *server, int channel_id);

/**
*  @brief Removes any "zombie" connections from the server and the world. A zombie connection is a connection that hasn't sent anything in X seconds
*
*  @param server The server with the connections
*  @param world The world.
*/
int udp_remove_zombie_connections(ServerUDP *server, World *world);

#endif
