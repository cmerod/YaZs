#include "Server.h"
#pragma warning(disable : 4996)

ServerUDP server_init_UDP()
{
	ServerUDP server = {
        .num_clients = 0,
        .running = true,
        .client_msg.msg = {0}
    };
    timeManager_init(&server.timer);
    timeManager_start(&server.timer);
    
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(-1);
	}

	/* Open a socket */
	if (!(server.socket = SDLNet_UDP_Open(SERVER_PORT)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(-1);
	}

	/* Make space for the packet in*/
	if (!(server.packet_in = SDLNet_AllocPacket(1500)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	/* Make space for the packet out*/
	if (!(server.packet_out = SDLNet_AllocPacket(1500)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(-1);
	}
	for (int i = 0; i < MAX_SOCKETS; i++) // Create free sockets spaces for clients
	{
		memset(&server.clients[i], 0x00, sizeof(Client));
	}
	return server;
}

int server_quit_UDP(ServerUDP *server)
{
	SDLNet_FreePacket(server->packet_out);
    SDLNet_FreePacket(server->packet_in);
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

void server_recv(ServerUDP *server, World *world)
{
	if (udp_recv(server)) 
	{
		if (server_connection_is_new(*server) && server_allows_new_clients(*server)) 
		{
			int channelId = server_bind_adress_UDP(server);
            
            //Get a random spawn point on map
            Tile spawnPoint = LevelManager_get_random_player_spawn_tile(world->currentLevel);
			Avatar newPlayer = avatar_create(spawnPoint.destRect.x, spawnPoint.destRect.y, START_LIFE_PLAYER, SPEED_PLAYER, ++world->next_obj_id, PLAYER);
			world_add_avatar(world, newPlayer);
            
            //Send information to client about their id
            char outGoingCommand[10];
            sprintf(outGoingCommand, "%d %d", CLIENT_PLAYER_INFORMATION, newPlayer.obj_id);
            strcpy((char*)server->packet_out->data,outGoingCommand);
            server->packet_out->len = strlen(outGoingCommand);
            udp_send_singel_client(server, channelId);
		}

		commandManager_handel_incoming_packet(server, world);
	}
}



int server_connection_is_new(ServerUDP server)
{
    return server.packet_in->channel == -1; //-1 Means it's a new client
}

int server_allows_new_clients(ServerUDP server)
{
    return server.num_clients < MAX_SOCKETS && server.currentState == STATE_WAIT;
}

int server_bind_adress_UDP(ServerUDP *server)
{
    int i;
    for (i = 0; i < MAX_SOCKETS; i++)
    {
        if (server->clients[i].in_use == false){
            break;
        }
        
    }
    SDLNet_UDP_Bind(server->socket, i, &server->packet_in->address);
    
    server->clients[i].channel_id = i;
    server->clients[i].in_use = true;
    
    SDLNet_ResolveHost(&server->clients[i].client_address,(const char*)&server->packet_in->address.host,server->packet_in->address.port);
    
    server->num_clients++;
    server->packet_in->channel = i;
    
	return i;
}

int server_handle_client_input(UDPpacket *packet_in, bool input[MAX_PLAYERS][NUM_OF_KEYS])
{
	const char delim[2] = " ";
	char str[100] = { 0 };
	strcpy(str, (char*)packet_in->data);
	char *token;
	token = strtok(str, delim);
	int key = atoi(token);
	token = strtok(NULL, delim);
	int state = atoi(token);
	input[packet_in->channel][key] = state;
	memset(packet_in->data, 0, strlen((const char*)packet_in->data));
	return 0;
}

void server_player_hit(ServerUDP *server, World *world)
{
	int currentTime = timeManager_getTime(server->timer);
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (((currentTime - world->players.player[i].startTime) / 1000) > INVUL_TIME && world->players.player[i].hit) {
			world->players.player[i].hit = 0;
		}
	}
}

void server_update(ServerUDP *server, World *world)
{
	if (!server->timer.isPaused)
	{
		if (server->currentState == STATE_RUN || server->currentState == STATE_WAIT) {
			world_handle_event(world, server->timer);
		}
		server_game_state(world, server);
        if(server->currentState == STATE_RUN){
			server_player_hit(server, world);
			world_remove_enemy(world); 
            Uint32 currentTime = timeManager_getTime(server->timer);
            if (server->timer.isRunning &&
                (currentTime - world->lastSpawnTime) > world->nextSpawnTime &&
                world->enemies.num_enemies < MAX_ENEMIES && ((currentTime - server->startTime) / 1000) < ROUND_LEN)
            {
                world_spawn_enemy(world, server->timer);
            }
        }
	}
}

void server_send(ServerUDP *server, World *world)
{
	if (server->num_clients > 0 || world->players.connected > 0) {
		udp_remove_zombie_connections(server, world);
		udp_make_packet(server, world);
		udp_send(server);
	}
}

void server_add_outgoing_command(ServerUDP *server, char *cmd)
{
    char outGoingMsg[100] = {0};

    strcat(outGoingMsg, cmd);
    strcat(outGoingMsg,"\n");
    
    strcat(server->client_msg.msg, outGoingMsg);
}

void server_game_state(World *world, ServerUDP *server)
{
	Uint32 currentTime = timeManager_getTime(server->timer);

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (world->players.input[i][ENTER] == true && server->currentState == STATE_WAIT)
		{
			world->players.input[i][ENTER] = false;
			server->currentState = STATE_RUN;
			server->startTime = timeManager_getTime(server->timer);
		}
		else
			world->players.input[i][ENTER] = false;
	}
	if (server->currentState == STATE_RUN && ((currentTime - server->startTime) / 1000) > ROUND_LEN && world->enemies.num_enemies <= 0)
	{
		server->currentState = STATE_WIN;
		server->startTime = timeManager_getTime(server->timer);
	}
	else if (server->currentState == STATE_RUN)
	{
		int lost = world->players.connected;
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (world->players.player[i].in_use == true && world->players.player[i].life == 0) {
				lost--;
			}
		}
		if (lost <= 0)
		{
			server->currentState = STATE_LOST;
			server->startTime = timeManager_getTime(server->timer);
		}
	}
	if (server->currentState == STATE_WIN && ((currentTime - server->startTime) / 1000) > 3)
	{
		server->currentState = STATE_WAIT;
		if (world->currentLevel.number > LEVEL_3) {
			world_free_pathing_memory(world);
			*world = world_init();
			world->currentLevel = levelManager_get_level_with_id(1);
		}
		else {
			world_free_pathing_memory(world);
			world->currentLevel = levelManager_get_level_with_id(++world->currentLevel.number);
			world_set_life(world);
			for (int i = 0; i < MAX_PLAYERS; i++) {
				if (world->players.player[i].in_use == SDL_TRUE) {
					Tile spawnPoint = LevelManager_get_random_player_spawn_tile(world->currentLevel);
					world->players.player[i].rect_move_dst.x = spawnPoint.destRect.x;
					world->players.player[i].rect_move_dst.y = spawnPoint.destRect.y;
				}
			}
		}
	}
	if (server->currentState == STATE_LOST && ((currentTime - server->startTime) / 1000) > 3)
	{
		server->currentState = STATE_WAIT;
		world_free_pathing_memory(world);
		*world = world_init();
		world->currentLevel = levelManager_get_level_with_id(1);
	}
}
