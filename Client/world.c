#include "world.h"
#pragma warning(disable : 4996)

World world_init(SDL_Renderer *renderer)
{
	World world = {
		.players = { 0, {0}},
		.enemies = { 0, {0}, {0}}
    };
	char texturepath[100] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		TextureManager_create_texturepath(texturepath, "ZOMBIE", i);
		world.enemies.spr_move[i] = TextureManager_loadTexture(texturepath, renderer);
	}
	for (int i = 0; i < 5; i++)
	{
		TextureManager_create_texturepath(texturepath, "ZOMBIED", i);
		world.enemies.spr_death[i] = TextureManager_loadTexture(texturepath, renderer);
	}
	return world;
}

World world_reset(World *world)
{
	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(world->enemies.spr_death[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(world->enemies.spr_move[i]);
	}
	return EmptyWorld;
}

void world_update_player_dst(Player *player, Avatar avatar)
{
	if (player->avatar.rect_move_dst.x < avatar.rect_move_dst.x)
	{
		player->direction = ANIM_RIGHT;
	}
	else if (player->avatar.rect_move_dst.x > avatar.rect_move_dst.x)
	{
		player->direction = ANIM_LEFT;
	}
	if (player->avatar.rect_move_dst.y < avatar.rect_move_dst.y)
	{
		player->direction = ANIM_DOWN;
	}
	else if (player->avatar.rect_move_dst.y > avatar.rect_move_dst.y)
	{
		player->direction = ANIM_UP;
	}
	if (player->avatar.rect_move_dst.x == avatar.rect_move_dst.x &&
		player->avatar.rect_move_dst.y == avatar.rect_move_dst.y)
	{
		player->state = STATIONARY;
	}
	else { player->state = MOVING; }
	player->avatar.rect_move_dst = avatar.rect_move_dst;
}

void world_update_enemy_dst(Enemy *enemy, Avatar avatar)
{
	if (enemy->avatar.rect_move_dst.x < avatar.rect_move_dst.x)
	{
		enemy->direction = ANIM_RIGHT;
	}
	else if (enemy->avatar.rect_move_dst.x > avatar.rect_move_dst.x)
	{
		enemy->direction = ANIM_LEFT;
	}
	if (enemy->avatar.rect_move_dst.y < avatar.rect_move_dst.y)
	{
		enemy->direction = ANIM_DOWN;
	}
	else if (enemy->avatar.rect_move_dst.y > avatar.rect_move_dst.y)
	{
		enemy->direction = ANIM_UP;
	}
	enemy->avatar.rect_move_dst = avatar.rect_move_dst;
	if (enemy->avatar.life != avatar.life) {
		enemy->avatar.life = avatar.life;
		enemy->frameM = 0;
	}
}

void world_update_avatar(World *world, Avatar avatar, SDL_Renderer *renderer, Timer timer)
{
    //If the avatar does not exist in the world, we will create it.
    if(!world_has_avatar(*world, avatar)){
        SDL_Rect rect_move_src = {
            .x = 0,
            .y = 0,
            .w = 32,
            .h = 32,
        };
        
        printf("Avatar does not exist: %d\n", avatar.obj_id);
		if (avatar.cat == PLAYER)
		{	
			Player newPlayer = player_create_new(avatar, world->players.num_players, 0, 0, rect_move_src, renderer);
			world_add_player(world, newPlayer);	
		}
		else if (avatar.cat == ENEMY)
		{
			Enemy newEnemy = enemy_create(avatar, rect_move_src);
			world_add_enemy(world, newEnemy);
		}
		else if (avatar.cat == ATTACK)
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (world->players.player[i].avatar.obj_id == avatar.obj_id)
				{
					world->players.player[i].attack = avatar;
					world->players.player[i].frameM = 0;
					world->players.player[i].state = ATTACKING;
				}
			}
		}
    }
	if (avatar.cat == PLAYER) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (world->players.player[i].avatar.obj_id == avatar.obj_id)
			{
				if (world->players.player[i].avatar.life > avatar.life) {
					world->players.player[i].avatar.life = avatar.life;
					world->players.player[i].avatar.hit++;
					world->players.player[i].avatar.startTime = timeManager_getTime(timer);
				}
				world_update_player_dst(&world->players.player[i], avatar);
				if (world->players.player[i].avatar.life <= 0) {
					world->players.player[i].state = DYING;
				}
				break;
			}
		}
	}
	else if (avatar.cat == ATTACK) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (world->players.player[i].attack.obj_id == avatar.obj_id)
			{
				world->players.player[i].attack.rect_move_dst = avatar.rect_move_dst;
				world->players.player[i].state = ATTACKING;
				break;
			}
		}
	}
	else if (avatar.cat == ENEMY) {
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (world->enemies.enemy[i].avatar.obj_id == avatar.obj_id)
			{
				world_update_enemy_dst(&world->enemies.enemy[i], avatar);
				break;
			}
		}
	}
}

int world_has_avatar(World world, Avatar avatar)
{
	if (avatar.cat == PLAYER) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (world.players.player[i].avatar.obj_id == avatar.obj_id) {
				return world.players.player[i].avatar.in_use;
			}
		}
	}
	if (avatar.cat == ATTACK) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (world.players.player[i].attack.obj_id == avatar.obj_id) {
				return world.players.player[i].attack.in_use;
			}
		}
	}
	if (avatar.cat == ENEMY) {
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (world.enemies.enemy[i].avatar.obj_id == avatar.obj_id) {
				return world.enemies.enemy[i].avatar.in_use;
			}
		}
	}
    return 0;
}

void world_add_player(World *world, Player player)
{
	int id = 0;
	for (id = 0; id < MAX_PLAYERS; id++)
	{
		if (!world->players.player[id].avatar.in_use)
		{
			world->players.player[id] = player;
			world->players.num_players++;
			printf("Added player: %d\n", id);
			break;
		}
	}
}

void world_remove_avatar(World *world, int cat, int obj_id)
{
	int id = 0;
	if (cat == PLAYER)
	{
		for (id = 0; id < MAX_PLAYERS; id++)
		{
			if (world->players.player[id].avatar.obj_id == obj_id)
			{
				world->players.player[id] = EmptyPlayer;
				world->players.num_players--;
				break;
			}
		}
	}
	else if (cat == ENEMY)
	{
		for (id = 0; id < MAX_ENEMIES; id++)
		{
			if (world->enemies.enemy[id].avatar.obj_id == obj_id)
			{
				world->enemies.enemy[id].avatar.in_use = false;
				world->enemies.num_enemies--;
				break;
			}
		}
	}
}

void world_add_enemy(World *world, Enemy enemy)
{
	int id = 0;
	for (id = 0; id < MAX_ENEMIES; id++)
	{
		if (!world->enemies.enemy[id].avatar.in_use)
		{
			world->enemies.enemy[id] = enemy;
			world->enemies.num_enemies++;
            
			break;
		}
	}
}

int world_get_avatar_with_id(World *world, Avatar **avatar, int id, int cat)
{
	switch (cat) {
	case PLAYER:
		for (int i = 0; i < MAX_PLAYERS; i++) {

			if (world->players.player[i].avatar.obj_id == id &&
				world->players.player[i].avatar.in_use == true) {
				*avatar = &world->players.player[i].avatar;
				return 1;
			}
		}
		break;
	case ENEMY:
		for (int i = 0; i < MAX_ENEMIES; i++) {

			if (world->enemies.enemy[i].avatar.obj_id == id &&
				world->enemies.enemy[i].avatar.in_use == true) {
				*avatar = &world->enemies.enemy[i].avatar;
				return 1;
			}
		}
		break;
	case ATTACK:
		for (int i = 0; i < MAX_ENEMIES; i++) {

			if (world->players.player[i].attack.obj_id == id &&
				world->players.player[i].attack.in_use == true) {
				*avatar = &world->players.player[i].attack;
				return 1;
			}
		}
		break;
	}
    return 0;
}
