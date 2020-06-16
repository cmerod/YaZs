/* This code was collected from https://rosettacode.org/wiki/A*_search_algorithm on 17-05-2018
The page was last modified on 25 April 2018, at 17:00 when code was collected.
Content is available under GNU Free Documentation License 1.2 unless otherwise noted.
Modifications to suit the game has been made*/

#ifndef Pathing_h
#define Pathing_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
/* and not not_eq */
#include <iso646.h>
/* add -lm to command line to compile with this header */
#include <math.h>
#include "levelManager.h"

typedef struct pathfinder {
	int p_len;
	int * path;
	int c_len;
	int * closed;
	int o_len;
	int * open;
	int player_node;
	int enemy_node;
} Pathfinder;

/**
*  @brief Init a pathfinder struct
*
*/
Pathfinder pathing_init(void);

/**
*  @brief Searches a path for the enemy to player
*
*  @param pathfinder Contains variables to make search
*  @param level Contains the map and neccesary variables to do the search
*  @param player_node The tile on which the player is currently located on (destination)
*  @param enemy_node The tile on which the enemy is currently located on (start position)
*/
void pathing_search(Pathfinder *pathfinder, Level *level, int player_node, int enemy_node);

/**
*  @brief Clears routes of memory
*
*/
void pathing_free_routes(Level *level);

/**
*  @brief Free up memory from pathfinder struct
*
*/
void pathing_free_path(Pathfinder *pathfinder);
#endif /* Pathing_h */
