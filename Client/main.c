#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _WIN32_WINNT 0x0500
#include <windows.h>
#endif
#include "Game.h"
#include "Client.h"
#include "Input.h"
#include "soundManager.h"
#include "Scenes/sceneManager.h"
#include "Scenes/sceneDefenitions.h"
#include "Command/commandList.h"


#pragma warning(disable : 4996)

int main(int argc, char * argv[]){

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);  //won't hide the window without SW_MINIMIZE
	ShowWindow(hWnd, SW_HIDE);
#endif
	srand((unsigned int)time(NULL));
    
    Game game = game_init();
    soundManager_init();
    Frame frame = timeManager_frame_init(60, 1000);
    
    //"Global" var used throughout the games depending on current scene
	ClientUDP client = {0};
    World world;
    
    //Adds all the different scenes to the scene manager
    SceneManager sceneManager = sceneManager_new();
    sceneManager->clock.timer = &game.timer;
    sceneManager->add(scene_menu_main(), sceneManager);
    sceneManager->add(scene_menu_credits(), sceneManager);
    sceneManager->add(scene_menu_join(), sceneManager);
	sceneManager->add(scene_menu_host(), sceneManager);
    sceneManager->add(scene_run_game(), sceneManager);
	sceneManager->add(scene_intro_text(), sceneManager);
	sceneManager->add(scene_epilogue(), sceneManager);
    sceneManager->add(scene_menu_h2p(), sceneManager);
    
    //Load the first scene
    sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
 
    SDL_Event event;
    Command command;
    while(game.running)
    {
        frame.frameStart = SDL_GetTicks();
        
        //Check if a scene change needs to be done
        sceneManager->changeScene(&game, &world, &client, sceneManager);
        
        //Recive and parse any packets from the server
        commandManager_recv(&client);
        
        //Pull any commands from the server
        while(commandManager_pullCommands(&command)){
            sceneManager->currentScene->recv(command, &world, &game, &client, sceneManager);
        }
        
        //Handel user input
        while(SDL_PollEvent(&event)){
            sceneManager->currentScene->handelEvent(sceneManager, event, &game, &client);
            
            if(event.type == SDL_QUIT){
                game.running = SDL_FALSE;
                break;
            };
        };
        
        sceneManager->currentScene->update(sceneManager, &client, &world);
        sceneManager->currentScene->render(&world, &game, sceneManager->currentScene);
    
        timeManager_cap_frames(&frame);
    }
    
    //Remember to clean up command list malloc
    //Frees up memory from heap
    sceneManager_destroy(sceneManager);
    soundManager_destroy();
    game_quit(&game, &client);
    return 0;
}
