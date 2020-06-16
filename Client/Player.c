#include "Player.h"
#pragma warning(disable : 4996)

Player player_create_new(Avatar avatar, int play_num, int frameM, int direction, SDL_Rect rect_move_src, SDL_Renderer *renderer)
{
	char texturepath[100] = { 0 };
	char name[3][100] = { {"MOVING"},{"ATTACKING"},{"DYING"} };
	Player player = {
		.spr_player[0] = {0},
		.spr_attack = {0},
		.frameM = frameM,
		.direction = direction,
		.state = 1,
        .rect_move_src = rect_move_src,
        .avatar = avatar,
		.attack = {0},
    };
	for (int i = 0; i < 3; i++)
	{
		TextureManager_create_texturepath(texturepath, name[i], play_num);
		player.spr_player[i] = TextureManager_loadTexture(texturepath, renderer);
	}
	player.spr_attack = TextureManager_loadTexture("Graphics/ATTACK.png", renderer);
    return player;
}
void player_render(Player *player, SDL_Renderer *renderer)
{
	if (player->state == MOVING)
	{
		player_render_move(player, renderer);
	}
	else if (player->state == STATIONARY)
	{
		player_render_stationary(player, renderer);
	}
	else if (player->state == ATTACKING)
	{
		player_render_attack(player, renderer);
	}
	else if (player->state == DYING)
	{
		player_render_dying(player, renderer);
	}
}
void player_render_move(Player *player, SDL_Renderer *renderer)
{
	if (player->frameM / FRAME_COUNT >= 4)
	{
		player->frameM = 0;
	}
	player->rect_move_src.y = player->direction;
	if (player->frameM / FRAME_COUNT < 1)
	{
		player->rect_move_src.x = ANIM_1;
	}
	else if (player->frameM / FRAME_COUNT >= 1 && player->frameM / FRAME_COUNT < 2)
	{
		player->rect_move_src.x = ANIM_2;
	}
	else if (player->frameM / FRAME_COUNT >= 2 && player->frameM / FRAME_COUNT < 3)
	{
		player->rect_move_src.x = ANIM_3;
	}
	else if (player->frameM / FRAME_COUNT >= 3 && player->frameM / FRAME_COUNT < 4)
	{
		player->rect_move_src.x = ANIM_4;
	}
	if (player->avatar.hit > 0 && (player->avatar.hit % 4 == 0 || player->avatar.hit % 4 == 1)){
		player->avatar.hit++;
	}
	else {
		TextureManager_drawTexture(renderer, player->spr_player[MOVING], player->rect_move_src, player->avatar.rect_move_dst);
		if (player->avatar.hit > 0) {
			player->avatar.hit++;
		}
	}
	++player->frameM;
}
void player_render_stationary(Player *player, SDL_Renderer *renderer)
{
	player->rect_move_src.x = ANIM_1;
	player->rect_move_src.y = player->direction;
	if (player->avatar.hit > 0 && (player->avatar.hit % 4 == 0 || player->avatar.hit % 4 == 1)) {
		player->avatar.hit++;
	}
	else {
		TextureManager_drawTexture(renderer, player->spr_player[MOVING], player->rect_move_src, player->avatar.rect_move_dst);
		if (player->avatar.hit > 0) {
			player->avatar.hit++;
		}
	}
	player->frameM = 0;
}
void player_render_attack(Player *player, SDL_Renderer *renderer)
{
	if (player->frameM / FRAME_ATTACK >= 4)
	{
		player->state = MOVING;
		player->attack.in_use = false;
	}
	player->rect_move_src.y = player->direction;
	if (player->frameM / FRAME_ATTACK < 1)
	{
		player->rect_move_src.x = ANIM_1;
	}
	else if (player->frameM / FRAME_ATTACK >= 1 && player->frameM / FRAME_ATTACK < 2)
	{
		player->rect_move_src.x = ANIM_2;
	}
	else if (player->frameM / FRAME_ATTACK >= 2 && player->frameM / FRAME_ATTACK < 3)
	{
		player->rect_move_src.x = ANIM_3;
	}
	else if (player->frameM / FRAME_ATTACK >= 3 && player->frameM / FRAME_ATTACK < 4)
	{
		player->rect_move_src.x = ANIM_4;
	}
	if (player->avatar.hit > 0 && (player->avatar.hit % 4 == 0 || player->avatar.hit % 4 == 1)) {
		player->avatar.hit++;
	}
	else {
		TextureManager_drawTexture(renderer, player->spr_player[ATTACKING], player->rect_move_src, player->avatar.rect_move_dst);
		if (player->avatar.hit > 0) {
			player->avatar.hit++;
		}
	}
	TextureManager_drawTexture(renderer, player->spr_attack, player->rect_move_src, player->attack.rect_move_dst);
	++player->frameM;
}

void player_render_dying(Player *player, SDL_Renderer *renderer)
{
	if (player->frameM / FRAME_COUNT < 4)
	{
		player->rect_move_src.y = ANIM_DOWN;
	}
	else
	{
		player->rect_move_src.y = ANIM_LEFT;
	}
	if (player->frameM / FRAME_COUNT >= 8)
	{
		player->frameM = FRAME_COUNT * 4;
	}
	if (player->frameM / FRAME_COUNT < 1)
	{
		player->rect_move_src.x = ANIM_1;
	}
	else if (player->frameM / FRAME_COUNT >= 1 && player->frameM / FRAME_COUNT < 2)
	{
		player->rect_move_src.x = ANIM_2;
	}
	else if (player->frameM / FRAME_COUNT >= 2 && player->frameM / FRAME_COUNT < 3)
	{
		player->rect_move_src.x = ANIM_3;
	}
	else if (player->frameM / FRAME_COUNT >= 3 && player->frameM / FRAME_COUNT < 4)
	{
		player->rect_move_src.x = ANIM_4;
	}
	else if (player->frameM / FRAME_COUNT >= 4 && player->frameM / FRAME_COUNT < 5)
	{
		player->rect_move_src.x = ANIM_1;
	}
	else if (player->frameM / FRAME_COUNT >= 5 && player->frameM / FRAME_COUNT < 6)
	{
		player->rect_move_src.x = ANIM_2;
	}
	else if (player->frameM / FRAME_COUNT >= 6 && player->frameM / FRAME_COUNT < 7)
	{
		player->rect_move_src.x = ANIM_3;
	}
	else if (player->frameM / FRAME_COUNT >= 7 && player->frameM / FRAME_COUNT < 8)
	{
		player->rect_move_src.x = ANIM_4;
	}
	TextureManager_drawTexture(renderer, player->spr_player[DYING], player->rect_move_src, player->avatar.rect_move_dst);
	++player->frameM;
}
