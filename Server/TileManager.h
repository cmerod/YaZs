#ifndef TileManager_h
#define TileManager_h

#include <stdio.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/**
 *  @brief A map is built using tiles.
 */
typedef struct tile {
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    int type;
	int isWall; 
	int id; 
	
} Tile;


/**
 *  @brief Create the tile
 *
 *  @param type The type of tile
 *  @param srcRect The tiles srcRect (where in the texture it can be found)
 *  @param destRect The tiles destRect (where in the world it should be placed)
 */
Tile TileManager_createTile(int type, int isWall, SDL_Rect srcRect, SDL_Rect destRect);

#endif /* TileManager_h */
