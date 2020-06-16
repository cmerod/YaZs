#ifndef Enemy_h
#define Enemy_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif
#include "../Server/Avatar.h"
#include "TextureManager.h"
#include "Definitions.h"


typedef struct {
	Avatar avatar;
	int frameM, direction, texture_num;
	SDL_Rect rect_move_src;
} Enemy;


/**
*  @brief Create a new enemy (Intended for use by client, server will use an avatar struct instead)
*
*  @param avatar The avatar object
*  @param rect_move_src The location of enemy spawn sent by server to client
*/
Enemy enemy_create(Avatar avatar, SDL_Rect rect_move_src);

/**
*  @brief Render enemy avatar
*
*  @param enemy Contains data for location to render and direction obj is facing
*/
void enemy_render(Enemy *enemy);

/**
 *  @brief Render enemy death
 *
 *  @param enemy Contains data for location to render and direction obj is facing
 */
void enemy_render_death(Enemy *enemy);

#endif
