#ifndef levelManager_h
#define levelManager_h

#include <stdio.h>
#include <float.h>
#include "TileManager.h"
#include "../Client/Definitions.h"

/* description of graph node */
struct stop {
	double col, row;
	/* array of indexes of routes from this stop to neighbours in array of all routes */
	int * n;
	int n_len;
	double f, g, h;
	int from;
};

/* description of route between two nodes */
struct route {
	/* route has only one direction! */
	int x; /* index of stop in array of all stops of src of this route */
	int y; /* index of stop in array of all stops of dst of this route */
	double d;
};

typedef struct {
    int number;
    int map[LEVEL_TILE_HEIGHT][LEVEL_TILE_WIDTH];
    int spawnPoints[50][2];
    int numberOfSpawnPoints;
    Tile tile[LEVEL_TILE_HEIGHT][LEVEL_TILE_WIDTH];
    int isWall[30];
    int isWallLength;
    int playerSpawnPoints[10][2];
    int playerSpawnPointSize;
	int s_len;
	struct stop * stops;
	int r_len;
	struct route * routes;
} Level;

/**
 *  @brief Returns the level with corresponding id
 *
 *  @param id The level id
 */
Level levelManager_get_level_with_id(int id);

/**
 *  @brief Returns a tile marked for spawning
 *
 *  @param level The current level
 */
Tile LevelManager_get_random_spawn_tile(Level level);

/**
 *  @brief Returns a tile marked for player spawning
 *
 *  @param level The current level
 */
Tile LevelManager_get_random_player_spawn_tile(Level level);

/**
*  @brief Calculates the routes to all accessible neighbours for a tile and indexes all passable tiles.
*
*  @param level contains the map with tiles to calculate the routes for
*/
void levelManager_create_routes(Level *level);

/**
*  @brief Returns the requested tile
*
*  @param id The id of the tile requested
*  @param level Contains the tiles
*/
Tile levelManager_get_tile_with_id(int id, Level level);

#endif /* levelManager_h */
