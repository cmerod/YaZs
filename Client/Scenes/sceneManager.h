#ifndef sceneManager_h
#define sceneManager_h

#include <stdio.h>
#include <stdlib.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../world.h"
#include "../Game.h"
#include "../Client.h"
#include "../../Server/TimeManager.h"
#include "../soundManager.h"

#define MAX_SCENES 10
#define SCENE_MENU_MAIN 0
#define SCENE_MENU_CREDITS 1
#define SCENE_MENU_JOIN 2
#define SCENE_MENU_HOST 3
#define SCENE_RUN_GAME 4
#define SCENE_INTRO_TEXT 5
#define SCENE_EPILOGUE 6
#define SCENE_MENU_H2P 7


typedef struct sceneManager *SceneManager;
typedef struct scene *Scene;

struct scene{
    void (*init)(Game *game, World *world, ClientUDP *client, Scene scene);
    void (*recv)(Command command, World *world, Game *game, ClientUDP *client,SceneManager sceneManager);
    void (*handelEvent)(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client);
    void (*update)(SceneManager sceneManager, ClientUDP *client, World *world);
    void (*render)(World *world, Game *game, Scene scene);
    void (*remove)(Game *game, Scene self, World *world);
    void (*destroy)(Scene self);
    int number;
    int state;
	SDL_Texture *textures[20];
    Mix_Music *music[10];
	int Imagenumber;
};

struct sceneManager {
    Scene currentScene;
    bool newScene;
    int newSceneNumber;
    Scene scenes[MAX_SCENES];
    int numberOfScenes;
    void (*add)(Scene newScene, SceneManager);
    void (*loadScene)(int sceneNumber, SceneManager self);
    int (*changeScene)(Game *game, World *world, ClientUDP *client, SceneManager self);
    int (*try)(int seconds, SceneManager self);
    struct{
        Timer *timer;
        int startTime;
    } clock;
};

/**
 *  @brief Creates a new scene manager
 *
 */
SceneManager sceneManager_new(void);

/**
 *  @brief Destroys/frees all scenes and the manager it self
 *
 */
void sceneManager_destroy(SceneManager self);

#endif /* sceneManager_h */
