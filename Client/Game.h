#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <stdlib.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include "world.h"
#include "mapManager.h"
#include "../Server/TimeManager.h"
#include "Client.h"
#include "Command/commandManager.h"
#include "Definitions.h"

typedef struct {
    SDL_Surface* text;
    SDL_Texture* texture;
    int state;
    int numOfChars;
    SDL_bool running;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect rect;
    char ipstring[16];
    char tempstring[16];
    char textinput[20];
} Menu;

typedef struct game {
    SDL_bool running;
    Timer timer;
    int currentScene;
    struct {
        unsigned int w;
        unsigned int h;
        const char* name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* screenSurface;
    } screen;
    Menu menu;
    int client_id;
} Game;

Game game_init(void);
int game_quit(Game *self, ClientUDP *client);

#endif /* Game_h */
