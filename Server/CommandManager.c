#pragma warning(disable : 4996)

#include "CommandManager.h"

int commandManager_handel_incoming_packet(ServerUDP *server, World *world)
{
    char *commandStr = (char*)server->packet_in->data;
    int client_id = server->packet_in->channel;
    int commandType = atoi(&commandStr[0]);
    server->clients[client_id].lastTimeRecived = timeManager_getTime(server->timer);
    
    //Only handel input from connected clients
    if(client_id < 0){
        return 0;
    }
    
    switch (commandType) {
		case W:
		case A:
		case S:
		case D:
		case ESC:
		case SPACE:
		case ENTER:
			server_handle_client_input(server->packet_in, world->players.input);
			break;
		case KEEP_ALIVE_MSG_TYPE:
            break;
        case DISCONNECT_MSG_TYPE:
            world->players.player[client_id].remove = 1; //Flags the player for removal
            udp_unbind_address(server, client_id); //Removes the client from the server
            break;
        case CLIENT_CONNECT_MSG_TYPE:
            break;
		case SERVER_QUIT:
			server->running = SDL_FALSE;
			break;
        default:
            break;
    }
    
    return 0;
}
