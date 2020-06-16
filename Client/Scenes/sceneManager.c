#include "sceneManager.h"

static void add(Scene newScene, SceneManager self)
{
    if(newScene->number > MAX_SCENES){
        printf("Scene number is wrong, can't be over: %d, and is: %d\n", MAX_SCENES, newScene->number);
    }
    self->scenes[newScene->number] = newScene;
    self->numberOfScenes++;
}

static void setCurrent(int sceneNumber, SceneManager self)
{
    self->newSceneNumber = sceneNumber;
    self->newScene = SDL_TRUE;
}

static int changeScene(Game *game, World *world, ClientUDP *client, SceneManager self)
{
    //No new scene change
    if(self->newScene == SDL_FALSE){
        return 0;
    }
    
    if(self->currentScene != NULL){
        self->currentScene->remove(game, self->currentScene, world);
    }
    
    self->currentScene = self->scenes[self->newSceneNumber];
    
    if(self->currentScene == NULL){
        printf("Could not find scene: %d maybe you forgot to add it?\n", self->newSceneNumber);
    }
    
    self->currentScene->init(game, world, client, self->currentScene);
    
    //Reset new scene values
    self->newScene = SDL_FALSE;
    self->newSceneNumber = -1;
	self->clock.startTime = 0;
    return 1;
}

static int try(int seconds, SceneManager self)
{
    int currentTime = timeManager_getTime(*self->clock.timer);
    
    if(self->clock.startTime == 0){
        self->clock.startTime = currentTime;
    }

    if(((currentTime - self->clock.startTime) / 1000) > seconds){
        self->clock.startTime = 0;
        return 0;
    }
    
    return 1;
}

SceneManager sceneManager_new(void)
{
    SceneManager self = malloc(sizeof(struct sceneManager));
    self->numberOfScenes = 0;
    self->add = add;
    self->loadScene = setCurrent;
    self->changeScene = changeScene;
    self->try = try;
    self->newScene = SDL_FALSE;
    self->newSceneNumber = -1;
    self->clock.startTime = 0;
	self->currentScene = NULL;

    return self;
}

void sceneManager_destroy(SceneManager self)
{
    Scene scene;
    for(int i = 0; i < self->numberOfScenes; i++){
        scene = self->scenes[i];

        if(scene != NULL){
            scene->destroy(scene);
        }
    }
    
    free(self);
}
