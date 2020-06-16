#ifndef commandManager_h
#define commandManager_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif
#include <stdarg.h>
#include "../../Server/CommandDefinitions.h"
#include "../Client.h"
#include "commandList.h"

/**
 *  @brief Sends a keep-alive msg to connected server.
 *
 *  @note Look in "CommandDefinitions.h" to see how the msg is formated and what type it has
 *
 *  @param client The client that sends the msg
 */
void commandManager_sendKeepAlive(ClientUDP *client);

/**
 *  @brief Sends a disconnect msg to connected server.
 *
 *  @note Look in "CommandDefinitions.h" to see how the msg is formated and what type it has
 *
 *  @param client The client that sends the msg
 */
void commandManager_sendDisconnect(ClientUDP *client);

/**
 *  @brief Sends a connect msg to connected server.
 *
 *  @note Look in "CommandDefinitions.h" to see how the msg is formated and what type it has
 *
 *  @param client The client that sends the msg
 */
void commandManager_sendConnect(ClientUDP *client);

/**
 *  @brief Checks if theres any commands to recive from the server, if so, adds them to the command list
 */
void commandManager_recv(ClientUDP *client);

/**
 *  @brief Pulls any commands from the command list
 */
int commandManager_pullCommands(Command *command);

/**
*  @brief Sends a command for the server to exit
*/
void commandManager_server_quit(ClientUDP *client);

#endif /* commandManager_h */
