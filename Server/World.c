#include "World.h"

World world_init(void)
{
    World world = {
        .next_obj_id = 0,
		.players = {
            .connected = 0,
            .player = EmptyAvatar,
			.attack = EmptyAvatar,
			.input = {0}
        },
		.enemies = {
			.num_enemies = 0,
			.enemy = {0},
			.path = {0}
		},
    .currentLevel = {0},
		.lastSpawnTime = SDL_GetTicks(),
		.nextSpawnTime = rand() % 800 + 100,
    };
    
    return world;
}
int world_add_avatar(World *world, Avatar player)
{
    int id = 0;
    for(id = 0; id < MAX_PLAYERS; id++){
        if(!world->players.player[id].in_use){
            world->players.player[id] = player;
            world->players.connected++;
            return 0;
        }
    }
    return 1;
}

void world_handle_event(World *world, Timer timer)
{
	world_move_avatar(world); 
	world_attack(world, timer);
	world_collision_detect(world, timer);
}

void world_collision_detect(World *world, Timer timer)
{
	for (int i = 0;i < MAX_PLAYERS;i++) {
		if (world->players.player[i].in_use == true && world->players.player[i].life > 0) {
			for (int j = 0;j < MAX_ENEMIES;j++) {
				if (world->enemies.enemy[j].in_use == true && world->enemies.enemy[j].life > 0) {
					if (pixel_avatar_colission(&world->players.player[i].hitbox, 1, &world->enemies.enemy[j].hitbox, 1) && !world->players.player[i].hit) {
						world->players.player[i].life--;
						world->players.player[i].hit = 1;
						world->players.player[i].startTime = timeManager_getTime(timer);
						break;
					}
					if (world->players.attack[i].in_use) {
						if (pixel_avatar_colission(&world->players.attack[i].hitbox, 3, &world->enemies.enemy[j].hitbox, 1)) {
							world->players.player[i].score++;
							world->enemies.enemy[j].life--;
							world->enemies.enemy[j].speed = 0;
						}
						if (pixel_avatar_colission(&world->players.player[i].hitbox, 1, &world->enemies.enemy[j].hitbox, 1)) {
							world->enemies.enemy[j].life--;
							world->enemies.enemy[j].speed = 0;
						}
					}
				}
			}
		}
	}
}

void world_move_avatar(World *world)
{
	for (int i = 0; i < MAX_PLAYERS;i++)
	{
		if (world->players.player[i].in_use == true && world->players.player[i].life > 0) 
		{
			Avatar avatar = avatar_move_player(&world->players.player[i], world->players.input[i], world->currentLevel);
			if (world->players.player[i].rect_move_dst.x > avatar.rect_move_dst.x)
			{
				world->players.direction[i] = ANIM_RIGHT;
			}
			else if (world->players.player[i].rect_move_dst.x < avatar.rect_move_dst.x)
			{
				world->players.direction[i] = ANIM_LEFT;
			}
			if (world->players.player[i].rect_move_dst.y > avatar.rect_move_dst.y)
			{
				world->players.direction[i] = ANIM_DOWN;
			}
			else if (world->players.player[i].rect_move_dst.y < avatar.rect_move_dst.y)
			{
				world->players.direction[i] = ANIM_UP;
			}
			pixel_update_hitbox(&world->players.player[i], world->players.direction[i]);
		}
	}
	int player_pos, enemy_pos;
	for (int i = 0; i < MAX_ENEMIES;i++) 
	{
		if (world->enemies.enemy[i].in_use == true && world->enemies.enemy[i].life > 0)
		{
			enemy_pos = world_get_avatar_pos(world->enemies.enemy[i], world->currentLevel);
			player_pos = world_get_avatar_pos(world->players.player[world_enemy_target(*world, i)], world->currentLevel);

			if (enemy_pos == player_pos) {
				avatar_move_enemy(&world->enemies.enemy[i], world->players.player[world_enemy_target(*world, i)], world->currentLevel);
				pixel_update_hitbox(&world->enemies.enemy[i], LATERAL);
			}
			else {
				if (world->enemies.path[i].enemy_node != enemy_pos || world->enemies.path[i].player_node != player_pos) {
					pathing_free_path(&world->enemies.path[i]);
					world->enemies.path[i] = pathing_init();

					for (int k = 0; k < world->currentLevel.s_len; k++) {
						world->currentLevel.stops[k].from = -1;
					}

					pathing_search(&world->enemies.path[i], &world->currentLevel, player_pos, enemy_pos);
				}
				if (world->enemies.path[i].path != NULL) {
					world_move_enemy(world->enemies.path[i], &world->enemies.enemy[i], world->currentLevel);
					pixel_update_hitbox(&world->enemies.enemy[i], LATERAL);
				}
			}
		}
	}
}

void world_move_enemy(Pathfinder path, Avatar *enemy, Level level)
{
	Tile next_t = levelManager_get_tile_with_id(path.path[path.p_len - 2], level);
	if (next_t.destRect.x < enemy->rect_move_dst.x)
	{
		enemy->rect_move_dst.x -= enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.x += enemy->speed;
		}
	}
	else if (next_t.destRect.x > enemy->rect_move_dst.x)
	{
		enemy->rect_move_dst.x += enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.x -= enemy->speed;
		}
	}
	if (next_t.destRect.y < enemy->rect_move_dst.y)
	{
		enemy->rect_move_dst.y -= enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.y += enemy->speed;
		}
	}
	else if (next_t.destRect.y > enemy->rect_move_dst.y)
	{
		enemy->rect_move_dst.y += enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.y -= enemy->speed;
		}
	}
}

int world_enemy_target(World world, int eid)
{
	int i, j;
	double targets[MAX_PLAYERS][2] = { 0 }, tmp;
	double posX = world.enemies.enemy[eid].rect_move_dst.x;
	double posY = world.enemies.enemy[eid].rect_move_dst.y;

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (world.players.player[i].in_use && world.players.player[i].life > 0) {
			targets[i][0] = i;
			targets[i][1] = hypot((posX - world.players.player[i].rect_move_dst.x), (posY - world.players.player[i].rect_move_dst.y));
		}
		else {
			targets[i][0] = i;
			targets[i][1] = DBL_MAX;
		}
	}
	for (j = 0; j < MAX_PLAYERS; j++) {
		for (i = 0; i < MAX_PLAYERS - 1 - j; i++) {
			if (targets[i][1] > targets[i + 1][1]) {
				tmp = targets[i][1];
				targets[i][1] = targets[i + 1][1];
				targets[i + 1][1] = tmp;
				tmp = targets[i][0];
				targets[i][0] = targets[i + 1][0];
				targets[i + 1][0] = tmp;
			}
		}
	}
	return targets[0][0];
}

int world_get_avatar_pos(Avatar avatar, Level level)
{
	for (int i = 0; i < LEVEL_TILE_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_TILE_WIDTH; j++) {
			if (level.tile[i][j].id >= 0 
				&& avatar.rect_move_dst.x + 16 >= level.tile[i][j].destRect.x
				&& avatar.rect_move_dst.x + 16 < level.tile[i][j].destRect.x + 32
				&& avatar.rect_move_dst.y + 16 >= level.tile[i][j].destRect.y
				&& avatar.rect_move_dst.y + 16 < level.tile[i][j].destRect.y + 32) {
				return level.tile[i][j].id;
			}
		}
	}
	return -1;
}

int world_has_avatar(World world, int obj_id)
{
    for(int i = 0; i < MAX_PLAYERS; i++){
        Avatar avatar = world.players.player[i];
        
        if(avatar.obj_id == obj_id){
            return (avatar.in_use && !avatar.remove);
        }
    }
    
    return 0;
}

int world_remove_avatar(World *world, int obj_id)
{
	Avatar avatar;
	for(int i = 0; i < MAX_PLAYERS; i++){
        avatar = world->players.player[i];
        if(avatar.obj_id == obj_id){
            world->players.player[i] = EmptyAvatar;
            world->players.connected--;
            return 1;
        }
    }
	for (int i = 0; i < MAX_ENEMIES; i++) {
		avatar = world->enemies.enemy[i];
		if (avatar.obj_id == obj_id) {
			world->enemies.enemy[i] = EmptyAvatar;
			pathing_free_path(&world->enemies.path[i]);
			world->enemies.num_enemies--;
			return 1;
		}
	}
    return 0;
}

int world_spawn_enemy(World *world, Timer timer) 
{
    Tile spawnTile = LevelManager_get_random_spawn_tile(world->currentLevel);
    Avatar avatar = avatar_create(spawnTile.destRect.x, spawnTile.destRect.y, LIFE_ENEMY, SPEED_ENEMY, ++world->next_obj_id, ENEMY);
	Pathfinder path = pathing_init();
    world->enemies.num_enemies++;
    world->lastSpawnTime = timeManager_getTime(timer);
    world->nextSpawnTime = (rand() % (850 / world->players.connected) + 100);
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (world->enemies.enemy[i].in_use == false)
        {
            world->enemies.enemy[i] = avatar;
			world->enemies.path[i] = path;
            break;
        }
    }
	return 0;
}

void world_remove_enemy(World *world)
{
	int j = 0;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (j < world->enemies.num_enemies)
		{
			if (world->enemies.enemy[i].in_use == true)
			{
				if (world->enemies.enemy[i].life < 1)
				{
					if (world->enemies.enemy[i].speed++ / FRAME_COUNT >= 4)
					{
						world->enemies.enemy[i] = EmptyAvatar;
						pathing_free_path(&world->enemies.path[i]);
						world->enemies.num_enemies--;
					}
				}
				j++;
			}
		}
		else { break; }
	}
}

void world_pause_game(World *world, Timer *timer)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (world->players.player[i].in_use == true)
		{
			if (world->players.input[i][ESC] == true && world->players.connected == 1 && timer->isPaused == false)
			{
				timeManager_pause(timer);
				world->players.input[i][ESC] = false;
			}
			else if (world->players.input[i][ESC] == true && world->players.connected == 1 && timer->isPaused == true)
			{
				timeManager_unpause(timer);
				world->players.input[i][ESC] = false;
			}
		}
	}
}

SDL_Rect world_attack_direction(World world, int i)
{
	SDL_Rect rect = { .h = 32,.w = 32 };
	if (world.players.direction[i] == ANIM_DOWN)
	{
		rect.x = world.players.player[i].rect_move_dst.x;
		rect.y = world.players.player[i].rect_move_dst.y + 32;
	}
	else if (world.players.direction[i] == ANIM_LEFT)
	{
		rect.x = world.players.player[i].rect_move_dst.x - 32;
		rect.y = world.players.player[i].rect_move_dst.y;
	}
	else if (world.players.direction[i] == ANIM_RIGHT)
	{
		rect.x = world.players.player[i].rect_move_dst.x + 32;
		rect.y = world.players.player[i].rect_move_dst.y;
	}
	else if (world.players.direction[i] == ANIM_UP)
	{
		rect.x = world.players.player[i].rect_move_dst.x;
		rect.y = world.players.player[i].rect_move_dst.y - 32;
	}
	return rect;
}

void world_attack(World *world, Timer timer)
{
	Uint32 currentTime = timeManager_getTime(timer);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if ((currentTime - world->players.attack[i].startTime) > ATTACK_SPEED)
		{
			if (world->players.input[i][SPACE] == true && world->players.attack[i].in_use == false && world->players.player[i].life > 0)
			{
				SDL_Rect rect = world_attack_direction(*world, i);
				world->players.attack[i] = avatar_create(rect.x, rect.y, NULL, NULL, world->players.player[i].obj_id, ATTACK);
				pixel_update_hitbox(&world->players.attack[i], world->players.direction[i]);
				world->players.input[i][SPACE] = false;
			}
			else if (world->players.attack[i].in_use == true)
			{
				world->players.attack[i].rect_move_dst = world_attack_direction(*world, i);
				pixel_update_hitbox(&world->players.attack[i], world->players.direction[i]);
				if (world->players.attack[i].speed++ / FRAME_ATTACK >= 4)
				{
					world->players.attack[i] = EmptyAvatar;
					world->players.attack[i].startTime = currentTime;
				}
				world->players.input[i][SPACE] = false;
			}
		}
		else {
			world->players.input[i][SPACE] = false;
		}
	}
}

void world_set_life(World *world)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (world->players.player[i].in_use == true)
			world->players.player[i].life = START_LIFE_PLAYER;
	}
}

void world_free_pathing_memory(World *world)
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (world->enemies.enemy[i].in_use) {
			pathing_free_path(&world->enemies.path[i]);
		}
	}
	pathing_free_routes(&world->currentLevel);
}
