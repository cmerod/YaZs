#include "commandManager.h"
#pragma warning(disable : 4996)

static node_t *commandList = NULL;

//Internal function, should only be accessed inside this function
static void commandManager_sendMsg(char *msg, ClientUDP *client)
{
    strcpy((char *)client->packet_out->data, msg);
    client_send_UDP(client);
}

/**
 *  @brief Parse the incoming packet from server and add commands to the command list
 *
 */
static void parse_server_packet(char *serverCommandStr)
{
    const char delimiter[2] = "\n";
    char *token;
    token = strtok(serverCommandStr, delimiter);
    
    
    while(token != NULL){
        int commandType = atoi(&token[0]);
        Command command;
        
        //Wierd code to move the pointer two points forward, to avoid reading commandType again
        token++;
        token++;
        
        switch(commandType){
            case SET_AVATAR_POSITION:
                sscanf( token, SET_AVATAR_POSITION_FORMAT, &command.avatar.cat, &command.avatar.obj_id, &command.avatar.life, &command.avatar.x, &command.avatar.y);
                command.avatar.type = SET_AVATAR_POSITION;
                command.type = SET_AVATAR_POSITION;
                break;
            case REMOVE_AVATAR_FROM_WORLD:
                sscanf(token, REMOVE_AVATAR_FROM_WORLD_FORMAT, &command.remove.cat, &command.remove.obj_id);
                command.remove.type = REMOVE_AVATAR_FROM_WORLD;
                command.type = REMOVE_AVATAR_FROM_WORLD;
                break;
            case GAME_INFO:
                sscanf(token, GAME_INFO_FORMAT, &command.game.state, &command.game.map);
                command.game.type = GAME_INFO_TYPE;
                command.type = GAME_INFO_TYPE;
                break;
            case CLIENT_PLAYER_INFORMATION:
                sscanf(token, CLIENT_PLAYER_INFORMATION_FORMAT, &command.client.client_id);
                command.client.type = CLIENT_PLAYER_INFORMATION;
                command.type = CLIENT_PLAYER_INFORMATION;
                break;
            default:
                printf("Command: %d not found\n", commandType);
                continue;
        }

        token = strtok(NULL, delimiter);
        commandList_push(&commandList, command);
    }
}

void commandManager_sendKeepAlive(ClientUDP *client)
{
	char msg[100] = { 0 };
	int msg_type = KEEP_ALIVE_MSG_TYPE;
	sprintf(msg, "%d", msg_type);

  commandManager_sendMsg(msg, client);
}

void commandManager_sendDisconnect(ClientUDP *client)
{
    char msg[100] = {0};
    int msg_type = DISCONNECT_MSG_TYPE;
	sprintf(msg, "%d", msg_type);

    commandManager_sendMsg(msg, client);
}

void commandManager_sendConnect(ClientUDP *client)
{
    char msg[3] = {0};
    int msg_type = CLIENT_CONNECT_MSG_TYPE;
    sprintf(msg,"%d", msg_type);
    commandManager_sendMsg(msg,client);
}

void commandManager_recv(ClientUDP *client)
{
    while(client_recv_UDP(client)){
		parse_server_packet((char*)client->packet_in->data);
    }
}

int commandManager_pullCommands(Command *command)
{
    
    //The list is empty
    if(commandList == NULL){
        return 0;
    }
    
    *command = commandList_pop(&commandList);
    return 1;
}

void commandManager_server_quit(ClientUDP *client)
{
	char msg[100] = { 0 };
	int msg_type = SERVER_QUIT;
	sprintf(msg, "%d", msg_type);
	commandManager_sendMsg(msg, client);
}
