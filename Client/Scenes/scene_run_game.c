#include "scene_run_game.h"

static void init(Game *game, World *world, ClientUDP *client, Scene scene)
{
	scene->state = STATE_WAIT;
    scene->textures[ESC_MENU] = TextureManager_loadTexture("Graphics/ESC-menu.png", game->screen.renderer);
    scene->textures[PLAYER_HEART] = TextureManager_loadTexture("Graphics/Liv1.png", game->screen.renderer);
    scene->textures[PLAYER_HEART_EMPTY] = TextureManager_loadTexture("Graphics/Liv2.png", game->screen.renderer);
    scene->textures[PRESS_ENTER_TO_START] = TextureManager_loadTexture("Graphics/press_enter_to_start.png", game->screen.renderer);
	scene->textures[PLAYER_MODEL_1] = TextureManager_loadTexture("Graphics/MOVING0.png", game->screen.renderer);
	scene->textures[PLAYER_MODEL_2] = TextureManager_loadTexture("Graphics/MOVING1.png", game->screen.renderer);
	scene->textures[PLAYER_MODEL_3] = TextureManager_loadTexture("Graphics/MOVING2.png", game->screen.renderer);
	scene->textures[PLAYER_MODEL_4] = TextureManager_loadTexture("Graphics/MOVING3.png", game->screen.renderer);
	scene->textures[GAME_WON] = TextureManager_loadTexture("Graphics/GAME_WON.png", game->screen.renderer);
	scene->textures[GAME_LOST] = TextureManager_loadTexture("Graphics/GAME_LOST.png", game->screen.renderer);
    
    soundManager_loadChunk("Music/slag.wav");
	soundManager_loadDie("Music/GameOver.wav");
}

static void recv(Command command, World *world, Game *game, ClientUDP *client, SceneManager sceneManager)
{
    switch (command.type) {
        case AVATAR_POSITION:;
            Avatar avatar = avatar_create(command.avatar.x, command.avatar.y, command.avatar.life, SPEED_PLAYER, command.avatar.obj_id, command.avatar.cat);
            world_update_avatar(world, avatar, game->screen.renderer, game->timer);
            break;
        case AVATAR_REMOVE:
            world_remove_avatar(world, command.remove.cat, command.remove.obj_id);
            break;
        case GAME_INFO_TYPE:
            if( sceneManager->currentScene->state == STATE_WAITING && command.game.state == STATE_RUNNING){
                sceneManager->currentScene->state = STATE_RUNNING;
            }
            if(command.game.state == STATE_WIN){
				sceneManager->currentScene->state = STATE_WON;
            } 
			if (command.game.state == STATE_LOST){
				if (sceneManager->currentScene->state != STATE_GAME_OVER)
				{
					soundManager_pauseMusic();
					soundManager_playDie(0);
				}
				sceneManager->currentScene->state = STATE_GAME_OVER;
			}
            break;
        default:
            break;
    }
}
static void handelEvent(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
    input_key_press(event, client);

    if (event.type == SDL_KEYDOWN &&
        event.key.repeat == 0 &&
        event.key.keysym.sym == SDLK_ESCAPE){
        Scene currentScene = sceneManager->currentScene;
        
        //Maybe we should change this so that the actual game pauses instead of just state change
        if(currentScene->state == STATE_RUNNING || currentScene->state == STATE_WAITING){
            currentScene->state = STATE_PAUSED;
        }
        else if(currentScene->state == STATE_PAUSED){
            currentScene->state = STATE_RUNNING;
        }
    }
    
    //We only care about mouse input if the game is paused
    if(sceneManager->currentScene->state == STATE_PAUSED &&
       event.type == SDL_MOUSEBUTTONDOWN &&
       event.button.button == SDL_BUTTON_LEFT){
        if (event.button.x > BUTTON_RESUME_X_START &&
            event.button.x < BUTTON_RESUME_X_END &&
            event.button.y > BUTTON_RESUME_Y_START &&
            event.button.y < BUTTON_RESUME_Y_END) {
            sceneManager->currentScene->state = STATE_RUNNING;
            
            //Send information to the server that esc has been pressed
            input_make_str_true(client, ESC);
        }
        else if (event.button.x > BUTTON_QUIT_X_START &&
                 event.button.x < BUTTON_QUIT_X_END &&
                 event.button.y > BUTTON_QUIT_Y_START &&
                 event.button.y < BUTTON_QUIT_Y_END)
			 {
				if(client->isHost){
					commandManager_server_quit(client);
				}
				else {
					input_make_str_true(client, ESC);
					commandManager_sendDisconnect(client);
				}
				sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
			 }   
    }
}

static void update(SceneManager sceneManager, ClientUDP *client, World *world)
{
    Uint32 currentTime = timeManager_getTime(*sceneManager->clock.timer);
    // The maxium time that can pass before the client needs to send a keep alive msg to the server
    Uint32 maxDisconnectTime = 5000;
    if(sceneManager->clock.timer->isRunning &&
       client->lastTimeSent != 0 &&
       (currentTime - client->lastTimeSent) > maxDisconnectTime){
        commandManager_sendKeepAlive(client);
    }
	if (sceneManager->currentScene->state == STATE_WON)
	{
		if (!sceneManager->try(3, sceneManager)) {
			if (world->currentLevel.number == 4){
				sceneManager->loadScene(SCENE_EPILOGUE, sceneManager);
			}
			else{
				sceneManager->loadScene(SCENE_INTRO_TEXT, sceneManager);
			}
		}
	}
	if (sceneManager->currentScene->state == STATE_GAME_OVER)
	{
		if (!sceneManager->try(3, sceneManager)) {
			if (client->isHost) {
				commandManager_server_quit(client);
			}
			else {
				commandManager_sendDisconnect(client);
			}
			sceneManager->loadScene(SCENE_MENU_MAIN, sceneManager);
		}
	}
}

static void render(World *world, Game *game, Scene scene)
{
	int i;
	SDL_RenderClear(game->screen.renderer);
	int currentTime = timeManager_getTime(game->timer);
    
    //Render map
    SDL_RenderCopy(game->screen.renderer, world->mapTexture, NULL, NULL);
    
    for (i = 0;i < MAX_PLAYERS;i++)
    {
        if (world->players.player[i].avatar.in_use == true)
        {
			if (((currentTime - world->players.player[i].avatar.startTime) / 1000) > INVUL_TIME && world->players.player[i].avatar.hit > 0) {
				world->players.player[i].avatar.hit = 0;
			}
			player_render(&world->players.player[i], game->screen.renderer);
        }
    }
    for (i = 0;i < MAX_ENEMIES;i++)
    {
        if (world->enemies.enemy[i].avatar.in_use == true)
        {
            if (world->enemies.enemy[i].avatar.life > 0)
            {
                enemy_render(&world->enemies.enemy[i]);
                TextureManager_drawTexture(game->screen.renderer, world->enemies.spr_move[world->enemies.enemy[i].texture_num],
                                           world->enemies.enemy[i].rect_move_src, world->enemies.enemy[i].avatar.rect_move_dst);
            }
            else
            {
                enemy_render_death(&world->enemies.enemy[i]);
                TextureManager_drawTexture(game->screen.renderer, world->enemies.spr_death[world->enemies.enemy[i].texture_num],
                                           world->enemies.enemy[i].rect_move_src, world->enemies.enemy[i].avatar.rect_move_dst);
                if (world->enemies.enemy[i].frameM / FRAME_COUNT >= 4)
                {
                    world->enemies.enemy[i].avatar = EmptyAvatar;
                    world->enemies.num_enemies--;
                }
            }
        }
    }
    
    if(scene->state == STATE_PAUSED){
        SDL_Rect srcRect = {
            .x = 0,
            .y = 0,
            .w = 282,
            .h = 197
        };
        SDL_Rect destRect = {
            .x = 259,
            .y = 222,
            .w = 282,
            .h = 197
        };
        SDL_RenderCopy(game->screen.renderer, scene->textures[ESC_MENU], &srcRect, &destRect);
    }

	SDL_Surface* levelSurf;
	SDL_Texture* levelText;

	SDL_Rect levelNr = {
		.x = 300,
		.y = 0,
		.w = 200,
		.h = 32
	};
	game->menu.color.r = 0;
	game->menu.color.g = 0;
	game->menu.color.b = 0;
	game->menu.color.a = 255;


	switch(world->currentLevel.number) {
		case 1:
			levelSurf = TTF_RenderText_Solid(game->menu.font, "LEVEL 1", game->menu.color);
			levelText = SDL_CreateTextureFromSurface(game->screen.renderer, levelSurf);
			SDL_FreeSurface(levelSurf);
			SDL_RenderCopy(game->screen.renderer, levelText, NULL, &levelNr);
			SDL_DestroyTexture(levelText);
			break;
		case 2:
			levelSurf = TTF_RenderText_Solid(game->menu.font, "LEVEL 2", game->menu.color);
			levelText = SDL_CreateTextureFromSurface(game->screen.renderer, levelSurf);
			SDL_FreeSurface(levelSurf);
			SDL_RenderCopy(game->screen.renderer, levelText, NULL, &levelNr);
			SDL_DestroyTexture(levelText);
			break;
        case 3:
            levelSurf = TTF_RenderText_Solid(game->menu.font, "LEVEL 3", game->menu.color);
            levelText = SDL_CreateTextureFromSurface(game->screen.renderer, levelSurf);
            SDL_FreeSurface(levelSurf);
            SDL_RenderCopy(game->screen.renderer, levelText, NULL, &levelNr);
            SDL_DestroyTexture(levelText);
            break;
        case 4:
            levelSurf = TTF_RenderText_Solid(game->menu.font, "LEVEL 4", game->menu.color);
            levelText = SDL_CreateTextureFromSurface(game->screen.renderer, levelSurf);
            SDL_FreeSurface(levelSurf);
            SDL_RenderCopy(game->screen.renderer, levelText, NULL, &levelNr);
            SDL_DestroyTexture(levelText);
            break;
	}

	SDL_Texture* YaZsText;
	SDL_Surface* YaZsSurf;
	SDL_Rect YaZsRect = {
		.x = 700,
		.y = 0,
		.w = 100,
		.h = 32
	};
	YaZsSurf = TTF_RenderText_Solid(game->menu.font, "YaZs", game->menu.color);
	YaZsText = SDL_CreateTextureFromSurface(game->screen.renderer, YaZsSurf);
	SDL_FreeSurface(YaZsSurf);
	SDL_RenderCopy(game->screen.renderer, YaZsText, NULL, &YaZsRect);
	SDL_DestroyTexture(YaZsText);


    //Render player life
    SDL_Rect lifeSrcRect = {
        .x = 0,
        .y = 0,
        .w = 96,
        .h = 96,
    };
    
    Avatar *currentPlayer;
	SDL_Texture *tempText = NULL;
    if(world_get_avatar_with_id(world, &currentPlayer, game->client_id, PLAYER)){
        SDL_Rect charSrc = {
            .x = 0,
            .y = 0,
            .w = 32,
            .h = 32
        };
        
        SDL_Rect charDest = {
            .x = 96,
            .y = 0,
            .w = 32,
            .h = 32,
        };
        
        switch (game->client_id) {
            case 1:
                tempText = scene->textures[PLAYER_MODEL_1];
                break;
            case 2:
                tempText = scene->textures[PLAYER_MODEL_2];
                break;
            case 3:
                tempText = scene->textures[PLAYER_MODEL_3];
                break;
            case 4:
                tempText = scene->textures[PLAYER_MODEL_4];
                break;
        }
        
        SDL_RenderCopy(game->screen.renderer, tempText, &charSrc, &charDest);
        
        for(i = 0; i < 3; i++){
            SDL_Rect lifeDestRect = {
                .x = 32 * i,
                .y = 0,
                .w = 32,
                .h = 32,
            };
            tempText = scene->textures[PLAYER_HEART];
            
            if(i > currentPlayer->life - 1){
                tempText = scene->textures[PLAYER_HEART_EMPTY];
            }
            
            SDL_RenderCopy(game->screen.renderer, tempText, &lifeSrcRect, &lifeDestRect);
        }

    }
	for (i = 0; i < MAX_PLAYERS; i++) {
		if (currentPlayer->obj_id == world->players.player[i].attack.obj_id && !world->players.player[i].attack.hit) {
			soundManager_playChunck(0);
			world->players.player[i].attack.hit++;
		}
	}
    
    if(scene->state == STATE_WAITING){
        SDL_Rect pressEnterToStartDestRect = {
            .x = (SCREEN_W / 2) - 240,
            .y = SCREEN_H - 100,
            .w = 480,
            .h = 60,
        };
        SDL_RenderCopy(game->screen.renderer, scene->textures[PRESS_ENTER_TO_START], NULL, &pressEnterToStartDestRect);
    }
	if (scene->state == STATE_WON) {
		SDL_Rect game_won = {
			.x = (SCREEN_W / 2) - 234,
			.y = (SCREEN_H / 2) - 30,
			.w = 468,
			.h = 60,
		};
		SDL_RenderCopy(game->screen.renderer, scene->textures[GAME_WON], NULL, &game_won);
	}
	if (scene->state == STATE_GAME_OVER) {
		SDL_Rect game_lost = {
			.x = (SCREEN_W / 2) - 234,
			.y = (SCREEN_H / 2) - 30,
			.w = 468,
			.h = 60,
		};
		SDL_RenderCopy(game->screen.renderer, scene->textures[GAME_LOST], NULL, &game_lost);
	}
    
    
    SDL_RenderPresent(game->screen.renderer);
}

static void remove_scene(Game *game, Scene self, World *world)
{
    SDL_DestroyTexture(self->textures[ESC_MENU]);
	SDL_DestroyTexture(self->textures[PLAYER_HEART]);
    SDL_DestroyTexture(self->textures[PLAYER_HEART_EMPTY]);
    SDL_DestroyTexture(self->textures[PRESS_ENTER_TO_START]);
    SDL_DestroyTexture(self->textures[PLAYER_MODEL_1]);
    SDL_DestroyTexture(self->textures[PLAYER_MODEL_2]);
    SDL_DestroyTexture(self->textures[PLAYER_MODEL_3]);
    SDL_DestroyTexture(self->textures[PLAYER_MODEL_4]);

    SDL_DestroyTexture(world->mapTexture);
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (world->players.player[i].avatar.in_use) {
			for (int j = 0; j < 3; j++) {
				SDL_DestroyTexture(world->players.player[i].spr_player[j]);
			}
			SDL_DestroyTexture(world->players.player[i].spr_attack);
		}
	}
	*world = world_reset(world);
    
    //Free up mem
    soundManager_closeChunk();
	soundManager_closeDie();
}

static void destroy(Scene self)
{
    free(self);
}

Scene scene_run_game(void)
{
    Scene scene = malloc(sizeof(struct scene));
    scene->init = init;
    scene->handelEvent = handelEvent;
    scene->recv = recv;
    scene->update = update;
    scene->render = render;
    scene->destroy = destroy;
    scene->remove = remove_scene;
    
    scene->number = SCENE_RUN_GAME;
    
    return scene;
}
