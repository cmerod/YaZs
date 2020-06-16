#ifndef World_h
#define World_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "Avatar.h"
#include "../Client/mapManager.h"
#include "../Client/Definitions.h"
#include "levelManager.h"
#include "TimeManager.h"
#include "Pixel.h"
#include "Pathing.h"

#define MAX_PLAYERS 4

typedef struct world {
	unsigned int next_obj_id;
	struct {
        int connected, direction[MAX_PLAYERS];
        Avatar player[MAX_PLAYERS];
		Avatar attack[MAX_PLAYERS];
		bool input[MAX_PLAYERS][NUM_OF_KEYS];
    } players;
	struct {
		int num_enemies;
		Avatar enemy[MAX_ENEMIES];
		Pathfinder path[MAX_ENEMIES];
	} enemies;
  Level currentLevel;
  Uint32 lastSpawnTime;
  Uint32 nextSpawnTime;
} World;

/**
 *  @brief Initialize the game world
 *
 */
World world_init(void);

/**
 *  @brief Adds a player to the world. Returns 0 on success and -1 on error.
 *
 *  @param world The world.
 *  @param player The player to be added.
 */
int world_add_avatar(World *world, Avatar player);

/**
 *  @brief Updates the world according to incomming events. Includes updating player and enemy positions.
 *		   Generating attacks and calculating collision detections. 
 *  @param world The world that will be updated
 *  @param timer A timer to calculate
 */
void world_handle_event(World *world, Timer timer);

/**
*  @brief Calculates collision detection between enemy/player and enemy/attack.
*
*/
void world_collision_detect(World *world, Timer timer);

/**
*  @brief Updates position on players and enemies
*
*/
void world_move_avatar(World *world);

/**
*  @brief Moves enemy accoring to calculated path
*
*/
void world_move_enemy(Pathfinder path, Avatar *enemy, Level level);

/**
*  @brief Calculates the enemy's target
*
*  @param world Contains all the player data
*  @param eid The spot in enemy array being compared with player positions
*/
int world_enemy_target(World world, int eid);

/**
*  @brief Returns the id of the tile the avatar is currently on
*
*  @param avatar The object which location is determined
*  @param level Contains the tiles
*/
int world_get_avatar_pos(Avatar avatar, Level level);

/**
 *  @brief Checks if the player exist in the world and that it hasn't been flagged for removal
 *
 *  @param world The world
 *  @param obj_id The avatars unique id
 *
 *  @return 1 if the avatar exist in the world. 0 if it doesn't exist or if it has been flagged for removal. -1 on error.
 */
int world_has_avatar(World world, int obj_id);

/**
 *  @brief Removes the avatar from the world.
 *
 *  @param world The world that will be updated
 *  @param obj_id The avatars unique id
 *
 *  @return Returns 1 on success, returns 0 if the avatar is not found. Returns -1 on error.
 */
int world_remove_avatar(World *world, int obj_id);

/**
*  @brief Spawns enemy in world using a random spawn tile. Time between spawns is randomized.
*
*  @param world The world that has an enemy added to it.
*/
int world_spawn_enemy(World *world, Timer timer);

/**
*  @brief Removes an enemy avatar object that has 0 in life and a certain amount of time has passed.
*
*  @param world Contains the enemies
*/
void world_remove_enemy(World *world);

/**
*  @brief Pauses and unpauses the game. Pauses game if only 1 player connected. 
*
*  @param world Contains the player inputs to check if pause is called
*  @param timer The timer that gets paused
*/
void world_pause_game(World *world, Timer *timer);

/**
*  @brief Creates attacks when client sends attack command, calculates position of attack object and determines when attack has ended.
*
*/
void world_attack(World *world, Timer timer);

/**
*  @brief Free up pathing memory when changing map
*
*/
void world_free_pathing_memory(World *world);
#endif /* World_h */
