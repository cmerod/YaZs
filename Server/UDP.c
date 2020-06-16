#include "UDP.h"
#pragma warning(disable : 4996)

int udp_recv(ServerUDP *server)
{
	return SDLNet_UDP_Recv(server->socket, server->packet_in);
}

int udp_send_singel_client(ServerUDP *server, int channel_id)
{
    if(server->packet_out->len <= 0){
        return -1;
    }
    
    SDLNet_UDP_Send(server->socket, channel_id, server->packet_out);
    
    return 0;
}

int udp_send(ServerUDP *server)
{
	if (server->packet_out->len > 0)
	{
		for (int i = 0; i < MAX_SOCKETS;i++)
		{
			if (server->clients[i].in_use != true) {
				continue;
			}

            udp_send_singel_client(server, i);
		}
        
        server->packet_out->len = 0;
        strcpy((char *)server->packet_out->data, "");
        
        server->client_msg.length = 0;
        strcpy((char *)server->client_msg.msg, "");
	}

	return 0;
}

int udp_make_packet(ServerUDP *server, World *world)
{
	char packetOutData[3000] = { 0 };
    
    char temp_game_info[10] = {0};
    sprintf(temp_game_info, "%d %d %d", GAME_INFO_TYPE, server->currentState, world->currentLevel.number);
    strcat(temp_game_info,"\n");
    strcpy((char*)server->packet_out->data, temp_game_info);

	Avatar temp_avatar;
	for (int i = 0; i < MAX_SOCKETS; i++) {

		temp_avatar = world->players.player[i];

		if (temp_avatar.in_use != true) {
			continue;
		}
		udp_convert_struct(packetOutData, temp_avatar);

		if (temp_avatar.remove) {
			world_remove_avatar(world, temp_avatar.obj_id);
		}
	}
	for (int i = 0; i < MAX_SOCKETS; i++) {

		temp_avatar = world->players.attack[i];

		if (temp_avatar.in_use != true) {
			continue;
		}
		udp_convert_struct(packetOutData, temp_avatar);
		if (temp_avatar.remove) {
			world_remove_avatar(world, temp_avatar.obj_id);
		}
	}

	for (int i = 0; i < MAX_ENEMIES; i++) {
		temp_avatar = world->enemies.enemy[i];

		if (temp_avatar.in_use != true) {

			continue;
		}

		udp_convert_struct(packetOutData, temp_avatar);

		if (temp_avatar.remove) {
			world_remove_avatar(world, temp_avatar.obj_id);
		}
	}

	strcat((char*)server->packet_out->data, packetOutData);
	server->packet_out->len = (int)strlen((char *)server->packet_out->data) + 1;
	return 0;
}

void udp_convert_struct(char *packetOutData, Avatar temp_avatar)
{
	int command;
	char command_in_str[3];

	command = SET_AVATAR_POSITION;
	if (temp_avatar.remove) {
		command = REMOVE_AVATAR_FROM_WORLD;
	}

	sprintf(command_in_str, "%d", command);
	strcat(packetOutData, command_in_str);
	strcat(packetOutData, " ");

	char temp_avatar_in_string[100] = { 0 };
	avatar_convert_to_string(temp_avatar, temp_avatar_in_string);

	strcat(packetOutData, temp_avatar_in_string);
	strcat(packetOutData, "\n");
}

int udp_unbind_address(ServerUDP *server, int channel_id)
{
	SDLNet_UDP_Unbind(server->socket, channel_id);
	server->clients[channel_id].in_use = false;
	server->num_clients--;
	return 0;
}

int udp_remove_zombie_connections(ServerUDP *server, World *world)
{
	if (!server->timer.isRunning) {
		return -1;
	}
	for (int i = 0; i < MAX_SOCKETS; i++) {
		Client client = server->clients[i];
		Uint32 currentTime = timeManager_getTime(server->timer);

		if (client.in_use && (currentTime - client.lastTimeRecived) > MAX_DISCONNECT_TIME) {
			if (world_has_avatar(*world, i)) {
				world->players.player[i].remove = 1;
			}
			udp_unbind_address(server, i);
		}
	}
	return 0;
}
