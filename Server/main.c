#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _WIN32_WINNT 0x0500
#include <windows.h>
#endif
#include "Server.h"
#include "CommandManager.h"

int main()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);
#endif
	
	srand((unsigned int)time(NULL));
	
	Frame frame = timeManager_frame_init(60, 1000);
	ServerUDP server = server_init_UDP();
    World world = world_init();
	printf("Before loading lvl\n\n");
    world.currentLevel = levelManager_get_level_with_id(1);
    server.currentState = STATE_WAIT;
    
	while (server.running) {
		
        frame.frameStart = SDL_GetTicks();
        server_recv(&server, &world); //Receive packets
        
		world_pause_game(&world, &server.timer); //Check if client paused game
    
		server_update(&server, &world); //Update gamestate
        
		server_send(&server, &world); //Make and send packages
		
		timeManager_cap_frames(&frame);  //Cap frames
	}
	server_quit_UDP(&server);

	return 0;
}


