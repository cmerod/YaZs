#include "scene_epilogue.h"

static void init(Game *game, World *world, ClientUDP *client, Scene scene)
{
	char texturepath[100] = { 0 };
	TextureManager_create_texturepath(texturepath, "EPILOGUE", 0);
	SDL_Texture *texture = TextureManager_loadTexture(texturepath, game->screen.renderer);
	scene->textures[0] = texture;
	scene->state = STATE_LOAD;
	scene->Imagenumber = 0;
}

static void recv(Command command, World *world, Game *game, ClientUDP *client, SceneManager sceneManager)
{
}

static void handelEvent(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (event.button.x < 792 &&
			event.button.x > 501 &&
			event.button.y < 628 &&
			event.button.y > 544) {
			if (client->isHost){
				commandManager_server_quit(client);
			}
			else {
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
	if (sceneManager->clock.timer->isRunning &&
		client->lastTimeSent != 0 &&
		(currentTime - client->lastTimeSent) > maxDisconnectTime) {
		commandManager_sendKeepAlive(client);
	}
}

static void render(World *world, Game *game, Scene scene)
{
	SDL_Rect src = { .h = 640,.w = 800,.y = 0 };

    SDL_RenderClear(game->screen.renderer);
    if (scene->Imagenumber / IMAGESHOWTIME < 1)
    {
        src.x = IMAGE_0;
    }
    else if (scene->Imagenumber / IMAGESHOWTIME >= 1 && scene->Imagenumber / IMAGESHOWTIME < 2)
    {
        src.x = IMAGE_1;
    }
    else if (scene->Imagenumber / IMAGESHOWTIME >= 2 && scene->Imagenumber / IMAGESHOWTIME < 3)
    {
        src.x = IMAGE_2;
    }
    else if (scene->Imagenumber / IMAGESHOWTIME >= 3)
    {
        src.x = IMAGE_3;
    }
    if (scene->Imagenumber / IMAGESHOWTIME < 3)
    {
        ++scene->Imagenumber;
    }
    SDL_RenderCopy(game->screen.renderer, scene->textures[0], &src, NULL);
    SDL_RenderPresent(game->screen.renderer);

}

static void remove_scene(Game *game, Scene scene, World *world)
{
	SDL_DestroyTexture(scene->textures[0]);
}

static void destroy(Scene self)
{
	free(self);
}

Scene scene_epilogue(void)
{
	Scene scene = malloc(sizeof(struct scene));
	scene->init = init;
	scene->handelEvent = handelEvent;
	scene->recv = recv;
	scene->update = update;
	scene->render = render;
	scene->destroy = destroy;
	scene->remove = remove_scene;

	scene->number = SCENE_EPILOGUE;

	return scene;
}
