#include "Game.h"

Game game_init(void)
{
    Game Game= {
        .running = SDL_FALSE,
        .screen = {
            .w = SCREEN_SCALE * SCREEN_W,
            .h = SCREEN_SCALE * SCREEN_H,
            .name = "YaZs",
            .window = NULL,
            .renderer = NULL,
        },
        .client_id = 0
    };
    timeManager_init(&Game.timer);
    timeManager_start(&Game.timer);
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL error -> %s\n", SDL_GetError());
        exit(1);
    }
    
    Game.screen.window = SDL_CreateWindow(Game.screen.name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Game.screen.w, Game.screen.h, SDL_WINDOW_SHOWN|SDL_WINDOW_ALWAYS_ON_TOP);
    
    if(Game.screen.window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }
    
    Game.screen.renderer = SDL_CreateRenderer(Game.screen.window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(Game.screen.renderer == NULL){
        printf("Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    
    SDL_SetRenderDrawColor(Game.screen.renderer, 150, 150, 150, 255);
    

    Game.running = SDL_TRUE;    
    return Game;
}

int game_quit(Game *self, ClientUDP *client)
{
	//Destroy the window and free memory
    SDL_DestroyRenderer(self->screen.renderer);
    SDL_DestroyWindow(self->screen.window);
    
    self->screen.window = NULL;
    self->screen.renderer = NULL;
    
	TTF_Quit();
    
    if(client->lastTimeSent > 0){
		if (client->isHost) {
			commandManager_server_quit(client);
		}
		else {
			//If we are connected to a server, send disconnect msg then quit SDL_NET
			commandManager_sendDisconnect(client);
		}
		client_quit_UDP(client);
    }

    
    timeManager_stop(&self->timer);

    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
