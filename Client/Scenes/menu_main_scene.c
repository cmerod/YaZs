#include "menu_main_scene.h"
#pragma warning(disable : 4996)

static void recv_menu(Command command, World *world, Game *game, ClientUDP *client, SceneManager SceneManager)
{
    
}

static void update(SceneManager SceneManager, ClientUDP *client, World * world)
{
	
}

static void render(World *world, Game *game, Scene scene)
{
    SDL_RenderClear(game->screen.renderer);
    SDL_RenderCopy(game->screen.renderer, game->menu.texture, NULL, NULL);
    SDL_RenderPresent(game->screen.renderer);
}

static void remove_menu(Game *game, Scene self, World *world)
{
    SDL_DestroyTexture(game->menu.texture);
    SDL_StopTextInput();
}

static void destroy(Scene self)
{
    free(self);
}

static Scene menu_scene_template()
{
    Scene scene = malloc(sizeof(struct scene));
    scene->recv = recv_menu;
    scene->update = update;
    scene->render = render;
    scene->destroy = destroy;
    scene->remove = remove_menu;
    
    return scene;
}

static Menu menu_default_init()
{
    TTF_Init();
    
    Menu menu = {
        .text = NULL,
        .state = 0,
        .numOfChars = 0,
        .running = SDL_TRUE,
        .font = TTF_OpenFont("bebas.ttf", 48),
        .color = {0xFF,0xFF,0xFF,0xFF},
        .rect = {160,150,33,90}
    };
    
    SDL_StartTextInput();
    
    return menu;
}

static void init_main_menu(Game *game, World *world, ClientUDP *client, Scene scene)
{
    Menu menu = menu_default_init();
    scene->textures[0] = TextureManager_loadTexture("Graphics/menu_main.png", game->screen.renderer);
	scene->textures[1] = TextureManager_loadTexture("Graphics/JOIN-HOST-menu.png", game->screen.renderer);
    game->menu = menu;
    
    soundManager_loadMusic("Music/bakgrund.mp3");
	scene->state = STATE_MAIN;
}

static void init_h2p_menu(Game *game, World *world, ClientUDP *client, Scene scene)
{
    Menu menu = menu_default_init();
    menu.texture = TextureManager_loadTexture("Graphics/menu_how2play.png", game->screen.renderer);
    game->menu = menu;
}

static void init_credits_menu(Game *game, World *world, ClientUDP *client, Scene scene)
{
    Menu menu = menu_default_init();
    
    menu.texture = TextureManager_loadTexture("Graphics/menu_credits.png", game->screen.renderer);
    
    game->menu = menu;
}

static void init_join_menu(Game *game, World *world, ClientUDP *client, Scene scene)
{
    Menu menu = menu_default_init();
    
    menu.texture = TextureManager_loadTexture("Graphics/menu_join.png", game->screen.renderer);
    
    game->menu = menu;
    scene->state = STATE_CONFIG;
}

static void handelEvent_main_menu(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        game->running = SDL_FALSE;
    }
    if(!soundManager_isMusicPlaying()){
        soundManager_playMusic(-1);
    }
    
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (sceneManager->currentScene->state == STATE_MAIN && 
			event.button.x > BUTTON_JOIN_X_START &&
			event.button.x < BUTTON_JOIN_X_END &&
			event.button.y > BUTTON_JOIN_Y_START &&
			event.button.y < BUTTON_JOIN_Y_END) {
			
			Scene currentScene = sceneManager->currentScene;
			currentScene->state = STATE_JOINHOST;
		}
		else if (sceneManager->currentScene->state == STATE_MAIN &&
			event.button.x > BUTTON_H2P_X_START &&
			event.button.x < BUTTON_H2P_X_END &&
			event.button.y > BUTTON_H2P_Y_START &&
			event.button.y < BUTTON_H2P_Y_END) {
			sceneManager->loadScene(SCENE_MENU_H2P, sceneManager);
		}
		else if (sceneManager->currentScene->state == STATE_MAIN &&
			event.button.x > BUTTON_CREDITS_X_START &&
			event.button.x < BUTTON_CREDITS_X_END &&
			event.button.y > BUTTON_CREDITS_Y_START &&
			event.button.y < BUTTON_CREDITS_Y_END) {
			sceneManager->loadScene(SCENE_MENU_CREDITS, sceneManager);
		}
		else if (sceneManager->currentScene->state == STATE_MAIN &&
			event.button.x > BUTTON_EXIT_X_START &&
			event.button.x < BUTTON_EXIT_X_END &&
			event.button.y > BUTTON_EXIT_Y_START  &&
			event.button.y < BUTTON_EXIT_Y_END) {
			game->running = SDL_FALSE;
		}
		else if (sceneManager->currentScene->state == STATE_JOINHOST && 
			event.button.x > BUTTON_HOST_X_START &&
			event.button.x < BUTTON_HOST_X_END &&
			event.button.y > BUTTON_HOST_Y_START &&
			event.button.y < BUTTON_HOST_Y_END) {
			sceneManager->loadScene(SCENE_MENU_HOST, sceneManager);

		}
		else if (sceneManager->currentScene->state == STATE_JOINHOST && 
			event.button.x > BUTTON_JOINGAME_X_START &&
			event.button.x < BUTTON_JOINGAME_X_END &&
			event.button.y > BUTTON_JOINGAME_Y_START &&
			event.button.y < BUTTON_JOINGAME_Y_END) {
			sceneManager->loadScene(SCENE_MENU_JOIN, sceneManager);
		}
		else if (sceneManager->currentScene->state == STATE_JOINHOST && 
			(event.button.x < 259 ||
			event.button.x > 541 ||
			event.button.y < 222 ||
			event.button.y > 414))
		{
			sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
		}
        else if (
                 event.button.x > BUTTON_MUTE_X_START &&
                 event.button.x < BUTTON_MUTE_X_END &&
                 event.button.y > BUTTON_MUTE_Y_START  &&
                 event.button.y < BUTTON_MUTE_Y_END) {
            soundManager_pauseMusic();
        }
        else if (
                 event.button.x > BUTTON_PLAY_X_START &&
                 event.button.x < BUTTON_PLAY_X_END &&
                 event.button.y > BUTTON_PLAY_Y_START  &&
                 event.button.y < BUTTON_PLAY_Y_END) {
            soundManager_resumeMusic();
        }
	}
  
  if (event.type == SDL_KEYDOWN &&
      event.key.keysym.sym == SDLK_ESCAPE &&
      sceneManager->currentScene->state == STATE_JOINHOST) {
        sceneManager->currentScene->state = STATE_MAIN;
  }
}

static void render_main(World *world, Game *game, Scene scene)
{
	SDL_RenderClear(game->screen.renderer);
	SDL_RenderCopy(game->screen.renderer, scene->textures[0], NULL, NULL);
	if (scene->state == STATE_JOINHOST) {
		SDL_Rect destRect = {
			.x = 259,
			.y = 222,
			.w = 282,
			.h = 197
		};
		SDL_RenderCopy(game->screen.renderer, scene->textures[1], NULL, &destRect);
	}
	SDL_RenderPresent(game->screen.renderer);
}

static void handelEvent_h2p_menu(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (event.button.x < 253 &&
            event.button.x > 23 &&
            event.button.y < 630 &&
            event.button.y > 548) {
            sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
        }
    }
}

static void handelEvent_credits_menu(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        if (event.button.x < 785 &&
            event.button.x > 643 &&
            event.button.y < 95 &&
            event.button.y > 10) {
            sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
        }
    }
}

static void handelEvent_join_menu(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    if(sceneManager->currentScene->state == STATE_CONFIG){
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x < 791 &&
				event.button.x > 604 &&
				event.button.y < 609 &&
				event.button.y > 546) {
				sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
			}
		}
        if (event.type == SDL_KEYDOWN || event.type == SDL_TEXTINPUT){
            if(event.key.keysym.sym == SDLK_ESCAPE){
                sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
            }

            else if(event.type == SDL_TEXTINPUT && game->menu.numOfChars<15){
                strcat(game->menu.textinput, event.text.text);
                game->menu.rect.w = game->menu.rect.w + 33;
                game->menu.numOfChars++;
            }
            else if(event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                strcpy(game->menu.textinput, SDL_GetClipboardText());
            }
            else if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(game->menu.textinput)>0){
                for (int i = 0;i < game->menu.numOfChars;i++) {
                    game->menu.tempstring[i] = game->menu.textinput[i];
                }
                memset(game->menu.textinput, 0, strlen(game->menu.textinput));
                for (int i = 0;i < game->menu.numOfChars;i++) {
                    if (i < (game->menu.numOfChars - 1)) {
                        game->menu.textinput[i] = game->menu.tempstring[i];
                    }
                }
                game->menu.rect.w = game->menu.rect.w - 33;
                game->menu.numOfChars--;
                memset(game->menu.tempstring, 0, strlen(game->menu.tempstring));
            }
            else if(event.key.keysym.sym == SDLK_RETURN){
                strcpy(game->menu.ipstring, game->menu.textinput);
                *client = client_init_UDP(game->menu.ipstring, 0);
                commandManager_sendConnect(client);
                sceneManager->currentScene->state = STATE_CONNECTING;
                
            }
        }
        else if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
            if (event.button.x < 475 &&
                event.button.x > 267 &&
                event.button.y < 517 &&
                event.button.y > 423) {
                strcpy(game->menu.ipstring, game->menu.textinput);
                *client = client_init_UDP(game->menu.ipstring, 0);
                commandManager_sendConnect(client);
                sceneManager->currentScene->state = STATE_CONNECTING;
            }
        }
    }else if(sceneManager->currentScene->state == STATE_ERROR_CONNECTING){
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
            sceneManager->loadScene(SCENE_MENU_JOIN, sceneManager);
        }
    }
    
}

static void handelEvent_host_menu(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    //Do nothing
}

static void update_join_menu(SceneManager SceneManager, ClientUDP *client, World *world)
{
    //If it has been 5 seconds this will return true
    if (SceneManager->currentScene->state == STATE_CONNECTING && !SceneManager->try(5, SceneManager)){
        SceneManager->currentScene->state = STATE_ERROR_CONNECTING;
    }else if (SceneManager->currentScene->state == STATE_ERROR_CONNECTING && !SceneManager->try(3, SceneManager)){
        SceneManager->loadScene(SCENE_MENU_JOIN, SceneManager);
    }
}

static void recv_join_menu(Command command, World *world, Game *game, ClientUDP *client,SceneManager sceneManager)
{
    //We have connected to the server, let's move to the next scene
    if(command.type == CLIENT_PLAYER_INFORMATION){
        game->client_id = command.client.client_id;
    }
    
    if(command.type == GAME_INFO_TYPE && game->client_id != 0){
        sceneManager->loadScene(SCENE_INTRO_TEXT, sceneManager);
    }
}

static void recv_host_menu(Command command, World *world, Game *game, ClientUDP *client,SceneManager sceneManager)
{
    //We have connected to the server, let's move to the next scene
    if(command.type == CLIENT_PLAYER_INFORMATION){
        game->client_id = command.client.client_id;
        sceneManager->loadScene(SCENE_INTRO_TEXT, sceneManager);
    }
}

static void render_join(World *world, Game *game, Scene scene)
{
    SDL_RenderClear(game->screen.renderer);
    SDL_RenderCopy(game->screen.renderer, game->menu.texture, NULL, NULL);
    
    if (strlen(game->menu.textinput) > 0) {
        game->menu.text = TTF_RenderText_Solid(game->menu.font, game->menu.textinput, game->menu.color);
        SDL_Texture* text = SDL_CreateTextureFromSurface(game->screen.renderer, game->menu.text);
        SDL_FreeSurface(game->menu.text);
        SDL_RenderCopy(game->screen.renderer, text, NULL, &game->menu.rect);
        SDL_DestroyTexture(text);
    }
    
    if(scene->state == STATE_CONNECTING){
        strcpy(game->menu.textinput,"Connecting...");
    }
    else if(scene->state == STATE_ERROR_CONNECTING){
        strcpy(game->menu.textinput,"Error  connecting!");
    }
    
    SDL_RenderPresent(game->screen.renderer);
}

static void init_host_menu(Game *game, World *world, ClientUDP *client, Scene scene)
{
	
	Menu menu = menu_default_init();

	menu.texture = TextureManager_loadTexture("Graphics/CONNECTING.png", game->screen.renderer);

	game->menu = menu;
	scene->state = STATE_CONFIG;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR szCmdline[] = TEXT("YaZsServer.exe");
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    if (!CreateProcess(NULL,		// No module name (use command line)
                       szCmdline,   // Command line
                       NULL,        // Process handle not inheritable
                       NULL,        // Thread handle not inheritable
                       0,           // Set handle inheritance to FALSE
                       0,           // No creation flags
                       NULL,        // Use parent's environment block
                       NULL,        // Use parent's starting directory
                       &si,         // Pointer to STARTUPINFO structure
                       &pi)         // Pointer to PROCESS_INFORMATION structure
       )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
    }
    else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        printf("Server initiated\n");
    }
#else
    char pathToServer[1024];
    uint32_t size = sizeof(pathToServer);
    if (_NSGetExecutablePath(pathToServer, &size) == 0)
        printf("executable path is %s\n", pathToServer);
    else
        printf("buffer too small; need size %u\n", size);
    
    char buffer[1024];
    char *p;
    p = strstr(pathToServer, "Game");
    strncpy(buffer, pathToServer, p-pathToServer);
    buffer[p-pathToServer] = '\0';
    strcat(buffer,"Server");

    int pid = fork();
    switch (pid) {
        case -1:
            printf("Error fork\n");
            break;
        case 0:
            pid = fork();
            switch (pid) {
                case -1:
                    printf("Error creating child fork\n");
                    break;
                case 0:
                    execl(buffer,"Server", NULL);
                    printf("Error starting server\n");
                    break;
                default:
                    exit(0);
                    break;
            }
        default:
            wait(0);
            printf("Created child with id: %i\n", pid);
            break;
    }
#endif
    
    strcpy(game->menu.ipstring, "127.0.0.1");
    *client = client_init_UDP(game->menu.ipstring, 1);
    scene->state = STATE_CONNECTING;
    SDL_Delay(500);
}

static void update_host_menu(SceneManager sceneManager, ClientUDP *client, World *world)
{
    if(sceneManager->currentScene->state == STATE_CONNECTING){
        commandManager_sendConnect(client);
    }
    
    //If it has been 5 seconds this will return true
    if (sceneManager->currentScene->state == STATE_CONNECTING && !sceneManager->try(5, sceneManager)){
        sceneManager->currentScene->state = STATE_ERROR_CONNECTING;
    }else if (sceneManager->currentScene->state == STATE_ERROR_CONNECTING && !sceneManager->try(3, sceneManager)){
        sceneManager->loadScene(SCENE_MENU_JOIN, sceneManager);
    }
}


Scene scene_menu_main()
{
    Scene scene = menu_scene_template();
    scene->init = init_main_menu;
    scene->handelEvent = handelEvent_main_menu;
	scene->render = render_main;

    scene->number = SCENE_MENU_MAIN;
    
    return scene;
}

Scene scene_menu_h2p()
{
    Scene scene = menu_scene_template();
    scene->init = init_h2p_menu;
    scene->handelEvent = handelEvent_h2p_menu;
    
    scene->number = SCENE_MENU_H2P;
    
    return scene;
}


Scene scene_menu_credits()
{
    Scene scene = menu_scene_template();
    scene->init = init_credits_menu;
    scene->handelEvent = handelEvent_credits_menu;

    scene->number = SCENE_MENU_CREDITS;
    
    return scene;
}

Scene scene_menu_join()
{
    Scene scene = menu_scene_template();
    scene->init = init_join_menu;
    scene->handelEvent = handelEvent_join_menu;
    scene->render = render_join;
    scene->update = update_join_menu;
    scene->recv = recv_join_menu;

    scene->number = SCENE_MENU_JOIN;
    
    return scene;
}

Scene scene_menu_host()
{
	Scene scene = menu_scene_template();
	scene->init = init_host_menu;
	scene->handelEvent = handelEvent_host_menu;
	scene->render = render;
	scene->update = update_host_menu;
	scene->recv = recv_host_menu;

	scene->number = SCENE_MENU_HOST;

	return scene;
}
