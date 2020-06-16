#include "Pixel.h"

int vert_x_offset = 15, vert_y_offset = 10, lat_x_offset = 13, lat_y_offset = 10, vert_player_w = 14,
vert_player_h = 22, lat_player_w = 11, lat_player_h = 22;

void pixel_create_hitbox(Avatar *avatar, int direction) {
	if (avatar->cat == PLAYER || avatar->cat == ENEMY) {
		for (int i = 0; i < 1; i++) {
			if (direction == ANIM_UP || direction == ANIM_DOWN) {
				avatar->hitbox[i].x = (avatar->rect_move_dst.x + vert_x_offset);
				avatar->hitbox[i].y = (avatar->rect_move_dst.y + vert_y_offset);
				avatar->hitbox[i].w = vert_player_w;
				avatar->hitbox[i].h = vert_player_h;
			}
			else if (direction == ANIM_LEFT || direction == ANIM_RIGHT) {
				avatar->hitbox[i].x = (avatar->rect_move_dst.x + lat_x_offset);
				avatar->hitbox[i].y = (avatar->rect_move_dst.y + lat_y_offset);
				avatar->hitbox[i].w = lat_player_w;
				avatar->hitbox[i].h = lat_player_h;
			}
		}
	}
	else if (avatar->cat == ATTACK) {
		if (direction == ANIM_UP) {
			avatar->hitbox[0].x = (avatar->rect_move_dst.x + 8);
			avatar->hitbox[0].y = (avatar->rect_move_dst.y);
			avatar->hitbox[0].w = 20;
			avatar->hitbox[0].h = 11;

			avatar->hitbox[1].x = (avatar->rect_move_dst.x);
			avatar->hitbox[1].y = (avatar->rect_move_dst.y + 12);
			avatar->hitbox[1].w = 32;
			avatar->hitbox[1].h = 9;

			avatar->hitbox[2].x = (avatar->rect_move_dst.x + 7);
			avatar->hitbox[2].y = (avatar->rect_move_dst.y + 21);
			avatar->hitbox[2].w = 20;
			avatar->hitbox[2].h = 12;
		}
		else if (direction == ANIM_DOWN) {
			avatar->hitbox[0].x = (avatar->rect_move_dst.x + 7);
			avatar->hitbox[0].y = (avatar->rect_move_dst.y);
			avatar->hitbox[0].w = 20;
			avatar->hitbox[0].h = 12;

			avatar->hitbox[1].x = (avatar->rect_move_dst.x);
			avatar->hitbox[1].y = (avatar->rect_move_dst.y + 13);
			avatar->hitbox[1].w = 32;
			avatar->hitbox[1].h = 9;

			avatar->hitbox[2].x = (avatar->rect_move_dst.x + 8);
			avatar->hitbox[2].y = (avatar->rect_move_dst.y + 22);
			avatar->hitbox[2].w = 20;
			avatar->hitbox[2].h = 11;
		}
		else if (direction == ANIM_LEFT) {
			avatar->hitbox[0].x = (avatar->rect_move_dst.x);
			avatar->hitbox[0].y = (avatar->rect_move_dst.y + 8);
			avatar->hitbox[0].w = 11;
			avatar->hitbox[0].h = 20;

			avatar->hitbox[1].x = (avatar->rect_move_dst.x + 12);
			avatar->hitbox[1].y = (avatar->rect_move_dst.y);
			avatar->hitbox[1].w = 9;
			avatar->hitbox[1].h = 32;

			avatar->hitbox[2].x = (avatar->rect_move_dst.x + 21);
			avatar->hitbox[2].y = (avatar->rect_move_dst.y + 7);
			avatar->hitbox[2].w = 12;
			avatar->hitbox[2].h = 20;
		}
		else if (direction == ANIM_RIGHT) {
			avatar->hitbox[0].x = (avatar->rect_move_dst.x);
			avatar->hitbox[0].y = (avatar->rect_move_dst.y + 7);
			avatar->hitbox[0].w = 12;
			avatar->hitbox[0].h = 20;

			avatar->hitbox[1].x = (avatar->rect_move_dst.x + 13);
			avatar->hitbox[1].y = (avatar->rect_move_dst.y);
			avatar->hitbox[1].w = 9;
			avatar->hitbox[1].h = 32;

			avatar->hitbox[2].x = (avatar->rect_move_dst.x + 21);
			avatar->hitbox[2].y = (avatar->rect_move_dst.y + 8);
			avatar->hitbox[2].w = 11;
			avatar->hitbox[2].h = 20;
		}
	}
}

void pixel_update_hitbox(Avatar *avatar, int direction) {
	if (direction == ANIM_LEFT || direction == ANIM_RIGHT) {
		pixel_create_hitbox(avatar, ANIM_LEFT);
	}
	else if (direction == ANIM_UP || direction == ANIM_DOWN) {
		pixel_create_hitbox(avatar, ANIM_DOWN);
	}
}

bool pixel_avatar_colission(SDL_Rect a[], int a_size, SDL_Rect b[], int b_size){
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	for (int i = 0; i < a_size; i++){
		leftA = a[i].x;
		rightA = a[i].x + a[i].w;
		topA = a[i].y;
		bottomA = a[i].y + a[i].h;

		for (int j = 0; j < b_size; j++){
			leftB = b[j].x;
			rightB = b[j].x + b[j].w;
			topB = b[j].y;
			bottomB = b[j].y + b[j].h;

			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false){
				return true;
			}
		}
	}
	return false;
}