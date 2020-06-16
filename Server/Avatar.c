#pragma warning(disable : 4996)

#include <stdarg.h>
#include "Avatar.h"

Avatar avatar_create(int posX, int posY, int life, int speed, int obj_id, int cat)
{
	Avatar avatar = {
		.life = life,
		.in_use = 1,
		.speed = speed,
		.remove = SDL_FALSE,
		.obj_id = obj_id,
		.cat = cat,
		.score = 0,
		.hit = 0,
		.startTime = 0,
		.rect_move_dst = {
            .w = 32,
            .h = 30,
            .x = posX,
            .y = posY
		},
		.hitbox = {0}
    };
    
    return avatar;
}
void convert_to_string(char* s, int numOfArgs, ...)
{
    int val = 0;
    va_list ap;
    int i;
    char temp_string[1000];
    va_start(ap, numOfArgs);
    for(i = 0; i < numOfArgs; i++) {
        val = va_arg(ap, int);
        sprintf(temp_string,"%d",val);
        strcat(s,temp_string);
        strcat(s," ");
    }
    va_end(ap);
}
void avatar_convert_to_string(Avatar avatar, char *playerConverted)
{
    convert_to_string(playerConverted,5,avatar.cat, avatar.obj_id, avatar.life, avatar.rect_move_dst.x,avatar.rect_move_dst.y);
} 

int avatar_collision_detect(Avatar *avatar, Level level)
{
	int x_overlaps, y_overlaps;
	for (int row = 0; row < LEVEL_TILE_HEIGHT; row++) {

		for (int column = 0; column < LEVEL_TILE_WIDTH; column++)
		{
			Tile t = level.tile[row][column];
			x_overlaps = 0;
			y_overlaps = 0;
			if (t.isWall)
			{
				if ((avatar->rect_move_dst.x < (t.destRect.x + t.destRect.w)) && ((avatar->rect_move_dst.x + avatar->rect_move_dst.w) >(t.destRect.x)))
				{
					x_overlaps = 1;
				}
				if ((avatar->rect_move_dst.y < (t.destRect.y + t.destRect.w)) && ((avatar->rect_move_dst.y + avatar->rect_move_dst.h) >(t.destRect.y)))
				{
					y_overlaps = 1;
				}
				if (x_overlaps == 1 && y_overlaps == 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

Avatar avatar_move_player(Avatar *player, bool input[], Level level)
{
	Avatar avatar = *player;

	if (input[W] == true && player->rect_move_dst.y >= 32)
	{
        player->rect_move_dst.y -= player->speed;
		if (avatar_collision_detect(player, level))
		{
			player->rect_move_dst.y += player->speed;
		}	
	}
	if (input[A] == true && player->rect_move_dst.x >= 0)
	{
		player->rect_move_dst.x -= player->speed;
		if (avatar_collision_detect(player, level))
		{
			player->rect_move_dst.x += player->speed;
		}
	}
	if (input[S] == true && player->rect_move_dst.y <= SCREEN_H - 32)
	{
		player->rect_move_dst.y += player->speed;
		if (avatar_collision_detect(player, level))
		{
			player->rect_move_dst.y -= player->speed;
		}
	}
	if (input[D] == true && player->rect_move_dst.x <= SCREEN_W - 32)
	{
		player->rect_move_dst.x += player->speed;
		if (avatar_collision_detect(player, level))
		{
			player->rect_move_dst.x -= player->speed;
		}
	}
	return avatar;
}

void avatar_move_enemy(Avatar *enemy, Avatar player, Level level)
{
	if (player.rect_move_dst.x < enemy->rect_move_dst.x)
	{
		enemy->rect_move_dst.x -= enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.x += enemy->speed;
		}
	}
	else if (player.rect_move_dst.x > enemy->rect_move_dst.x)
	{
		enemy->rect_move_dst.x += enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.x -= enemy->speed;
		}
	}
	if (player.rect_move_dst.y < enemy->rect_move_dst.y)
	{
		enemy->rect_move_dst.y -= enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.y += enemy->speed;
		}
	}
	else if (player.rect_move_dst.y > enemy->rect_move_dst.y)
	{
		enemy->rect_move_dst.y += enemy->speed;
		if (avatar_collision_detect(enemy, level))
		{
			enemy->rect_move_dst.y -= enemy->speed;
		}
	}
}

