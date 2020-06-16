#include "TileManager.h"

Tile TileManager_createTile(int tileType, int isWall, SDL_Rect srcRect, SDL_Rect destRect)
{   
    Tile tile = {
        .type = tileType,
		.isWall = isWall,
		.id = -1,
        .srcRect = srcRect,
        .destRect = destRect
    };
    
    return tile;
}
