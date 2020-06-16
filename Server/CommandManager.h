#ifndef CommandManager_h
#define CommandManager_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CommandDefinitions.h"
#include "World.h"
#include "Server.h"

/**
 *  @brief Takes a input from player/client and updates the world accordling
 *
 *  @param server The server/client with incoming packet
 *  @param world The world that needs updating
 */
int commandManager_handel_incoming_packet(ServerUDP *server, World *world);

#endif /* CommandManager_h */
