#ifndef world_h
#define world_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif

#include <stdio.h>
#include "TextureManager.h"
#include "../Server/Avatar.h"
#include "Player.h"
#include "Enemy.h"
#include "Definitions.h"
#include "mapManager.h"
#include "../Server/levelManager.h"
#include "../Server/TimeManager.h"

/**
 * @brief The structer that keeps track of everything that need to be rendered on screen.
 */

typedef struct world{
	struct {
		int num_players;
		Player player[MAX_PLAYERS];
	} players;
	struct {
		int num_enemies;
		Enemy enemy[MAX_ENEMIES];
		SDL_Texture* spr_move[5];
		SDL_Texture* spr_death[5];
	} enemies;
  Level currentLevel;
  SDL_Texture *mapTexture;
} World;

static const World EmptyWorld = { 0 };

World world_init(SDL_Renderer *renderer); // Init certain datapoints in the declared world struct.

/**
*  @brief Resets world struct
*
*/
World world_reset(World *world);

/**
 *  @brief Updates the avatar with new data
 *
 *  @note This function will create a new avatar if a avatar not exist
 */
void world_update_avatar(World *world, Avatar avatar, SDL_Renderer *renderer, Timer timer);

/**
 *  @brief Returns 1 if the avatar exist in the world, 0 if not. Returns -1 on error
 *
 *  @note This function will create a new avatar if a avatar not exist
 */
int world_has_avatar(World world, Avatar avatar);

/**
 *  @brief Adds the player to the world
 *
 */
void world_add_player(World *world, Player player);

/**
 *  @brief Removes an avatar from the world
 *
 *  @param world The world
 *  @param cat Category of avatar to be removed
 *  @param obj_id The avatars unique obj_id
 */
void world_remove_avatar(World *world, int cat, int obj_id);

/**
*  @brief Adds an enemy to the world
*
*/
void world_add_enemy(World *world, Enemy enemy);

/**
 *  @brief Gets the avatar from the world, returns 0 if no avatar is found
 *
 */
int world_get_avatar_with_id(World *world, Avatar **avatar, int id, int cat);
#endif /* world_h */
