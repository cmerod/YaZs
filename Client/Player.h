#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <stdlib.h>
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
	Avatar attack;
	int frameM, direction;
	int state;
	SDL_Texture* spr_player[3];
	SDL_Texture* spr_attack;
	SDL_Rect rect_move_src;
} Player;

static const Player EmptyPlayer = {0};

/**
*  @brief Render player avatar
*
*  @param player Contains data for location to render, if obj is moving, and direction obj is facing
*  @param renderer The renderer to render sprites
*/
void player_render(Player *player, SDL_Renderer *renderer);

/**
*  @brief Render player avatar as moving object. Belongs to function player_render.
*
*  @param player Contains data for location to render, if obj is moving, and direction obj is facing
*  @param renderer The renderer to render sprites
*/
void player_render_move(Player *player, SDL_Renderer *renderer);

/**
*  @brief Render player avatar as stationary. Belongs to function player_render.
*
*  @param player Contains data for location to render, if obj is moving, and direction obj is facing
*  @param renderer The renderer to render sprites
*/
void player_render_stationary(Player *player, SDL_Renderer *renderer);

/**
*  @brief Render player avatar when attacking. Belongs to function player render.
*
*  @param player Contains data for location to render, if obj is moving, and direction obj is facing
*  @param renderer The renderer to render sprites
*/
void player_render_attack(Player *player, SDL_Renderer *renderer);

/**
*  @brief Render when player is dying
*
*/
void player_render_dying(Player *player, SDL_Renderer *renderer);

/**
 *  @brief Creates a new player
 *
 *  @param avatar The avatar that will be linked with the player
 *  @param frameM The start frame for the animation (should always be 0)
 *  @param direction The direction the player is facing (should always be 0)
 *  @param rect_move_src Where in the texture the image can be found and how big the texture should be.
 */
Player player_create_new(Avatar avatar, int play_num, int frameM, int direction, SDL_Rect rect_move_src, SDL_Renderer *renderer);
#endif
