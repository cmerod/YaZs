#ifndef map_h
#define map_h

#include <stdio.h>
#include "TextureManager.h"
#include "../Server/TileManager.h"
#include "../Server/levelManager.h"
#include "Definitions.h"

typedef struct{
    char paths[LEVEL_MAX_NUM_TEXTURES][30];
    int numOfTextures;
} TexturePack;

/**
 *  @brief Loads the tiles in the map with correct textures
 *
 *  @param level The map
 *  @param renderer The SDL renderer
 */
void mapManager_loadTextures(Level *level, SDL_Texture **mapTexture, SDL_Renderer *renderer);

#endif /* map_h */
