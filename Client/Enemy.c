#include "Enemy.h"

Enemy enemy_create(Avatar avatar, SDL_Rect rect_move_src)
{
	Enemy enemy = {
		.avatar = avatar,
		.frameM = 0,
		.direction = 0,
		.texture_num = (rand() % 5),
		.rect_move_src = rect_move_src,
	};
	return enemy;
}

void enemy_render(Enemy *enemy)
{
	if (enemy->frameM / FRAME_COUNT >= 4)
	{
		enemy->frameM = 0;
	}
	enemy->rect_move_src.y = enemy->direction;
	if (enemy->frameM / FRAME_COUNT < 1)
	{
		enemy->rect_move_src.x = ANIM_1;
	}
	else if (enemy->frameM / FRAME_COUNT >= 1 && enemy->frameM / FRAME_COUNT < 2)
	{
		enemy->rect_move_src.x = ANIM_2;
	}
	else if (enemy->frameM / FRAME_COUNT >= 2 && enemy->frameM / FRAME_COUNT < 3)
	{
		enemy->rect_move_src.x = ANIM_3;
	}
	else if (enemy->frameM / FRAME_COUNT >= 3 && enemy->frameM / FRAME_COUNT < 4)
	{
		enemy->rect_move_src.x = ANIM_4;
	}
	++enemy->frameM;
}

void enemy_render_death(Enemy *enemy)
{
	enemy->rect_move_src.y = ANIM_DOWN;
	if (enemy->frameM / FRAME_COUNT < 1)
	{
		enemy->rect_move_src.x = ANIM_1;
	}
	else if (enemy->frameM / FRAME_COUNT >= 1 && enemy->frameM / FRAME_COUNT < 2)
	{
		enemy->rect_move_src.x = ANIM_2;
	}
	else if (enemy->frameM / FRAME_COUNT >= 2 && enemy->frameM / FRAME_COUNT < 3)
	{
		enemy->rect_move_src.x = ANIM_3;
	}
	else if (enemy->frameM / FRAME_COUNT >= 3 && enemy->frameM / FRAME_COUNT < 4)
	{
		enemy->rect_move_src.x = ANIM_4;
	}
	++enemy->frameM;
}