#ifndef Avatar_h
#define Avatar_h
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "levelManager.h"
#include "CommandDefinitions.h"
#include "../Client/Definitions.h"


typedef struct Avatar
{
  bool in_use;
  bool remove;
	int life, speed, obj_id, cat, score,hit, startTime;
	SDL_Rect rect_move_dst;
	SDL_Rect hitbox[3];
} Avatar;

static const Avatar EmptyAvatar = {0};

/**
 *  @brief Creates a new avatar
 *
 *  @param posX The avatars initial x-position
 *  @param posY The avatars initial y-position
 *  @param life The avatars total life
 *  @param speed The avatars movement speed
 *  @param obj_id The unique identifiera of the avatar
 *
 */
Avatar avatar_create(int posX, int posY, int life, int speed, int obj_id, int cat);

/**
 *  @brief Takes a player type and convert it into a string
 *
 *  @note For know the string will be a string that we can send directly to the client. However, in the future we prob should have some kind of ADT for commands that need to be sent to the client
 */
void avatar_convert_to_string(Avatar avatar, char *playerConverted);

/**
*  @brief Checks if avatar object has collided with wall tile
*
*/
int avatar_collision_detect(Avatar *avatar, Level level);

/**
 *  @brief Updates the player position according to event
 *
 *  @param player The player to be updated
 *  @param input The client input array belonging to the player
 */
Avatar avatar_move_player(Avatar *player, bool input[], Level level);

/**
*  @brief Updates enemy position
*
*  @param enemy The enemy to be updated
*  @param player The player the enemy follows TEMPORARY
*/
void avatar_move_enemy(Avatar *enemy, Avatar player, Level level);

#endif /* Avatar_h */
