#include "scene_intro_text.h"

static void init(Game *game, World *world, ClientUDP *client, Scene scene)
{
	char texturepath[100] = { 0 };

	for (int i = 0; i < 4; i++) {
		TextureManager_create_texturepath(texturepath, "LORE", i);
		SDL_Texture *texture = TextureManager_loadTexture(texturepath, game->screen.renderer);
		scene->textures[i] = texture;
	}
	*world = world_init(game->screen.renderer);
	scene->state = STATE_LOAD;
	scene->Imagenumber = 0;
}

static void recv(Command command, World *world, Game *game, ClientUDP *client, SceneManager sceneManager)
{
	if (command.type == GAME_INFO_TYPE && sceneManager->currentScene->state == STATE_LOAD && command.game.map != world->currentLevel.number) {
		world->currentLevel = levelManager_get_level_with_id(command.game.map);
        mapManager_loadTextures(&world->currentLevel, &world->mapTexture, game->screen.renderer);
		sceneManager->currentScene->state = STATE_COMPLETE;
	}
}

static void handelEvent(SceneManager sceneManager, SDL_Event event, Game *game, ClientUDP *client)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && sceneManager->currentScene->state == STATE_COMPLETE) {
		if (event.button.x < SCREEN_W &&
			event.button.x > 0 &&
			event.button.y < SCREEN_H &&
			event.button.y > 0) {
			sceneManager->loadScene(SCENE_RUN_GAME, sceneManager);
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
	SDL_Rect src = { .h=640,.w=800, .y=0 };
	if (world->currentLevel.number != 0) {
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
		SDL_RenderCopy(game->screen.renderer, scene->textures[world->currentLevel.number-1], &src, NULL);
		SDL_RenderPresent(game->screen.renderer);
	}
}

static void remove_scene(Game *game, Scene scene, World *world)
{
	for (int i = 0; i < 4; i++) {
		SDL_DestroyTexture(scene->textures[i]);
	}
}

static void destroy(Scene self)
{
	free(self);
}

Scene scene_intro_text(void)
{
	Scene scene = malloc(sizeof(struct scene));
	scene->init = init;
	scene->handelEvent = handelEvent;
	scene->recv = recv;
	scene->update = update;
	scene->render = render;
	scene->destroy = destroy;
	scene->remove = remove_scene;

	scene->number = SCENE_INTRO_TEXT;

	return scene;
}
