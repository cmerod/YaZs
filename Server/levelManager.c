#include "levelManager.h"

static Level get_level(int id)
{
    Level level_1 = {
        .number = 1,
        .map = {
            {28,28,28,28,28,28,28,28,28,28,30,30,30,30,30,28,28,28,28,28,28,28,28,28,28},
            {28,23,21,21,32,21,21,21,21,24,0,1,0,1,0,23,21,21,21,21,21,32,32,24,28},
            {28,22,1,0,1,0,1,0,1,27,1,0,1,0,1,22,15,15,15,12,6,19,20,27,28},
            {28,22,0,16,17,2,3,18,0,27,0,1,0,1,0,22,15,15,15,15,15,15,15,27,28},
            {28,22,1,16,7,4,9,18,1,27,1,0,1,0,1,22,15,15,15,13,13,15,15,27,28},
            {28,33,0,16,8,17,17,18,0,27,0,1,0,1,0,22,15,15,15,10,11,15,15,27,28},
            {28,22,1,16,17,17,17,18,1,0,1,0,1,0,1,0,15,15,15,15,15,15,15,27,28},
            {28,22,0,1,0,1,0,1,0,1,0,1,0,1,0,1,15,15,15,15,15,15,15,27,28},
            {28,22,21,21,21,21,21,21,21,24,1,0,1,0,1,23,21,21,21,44,21,21,21,27,28},
            {28,22,38,38,0,1,5,5,0,27,0,1,0,1,0,22,37,43,34,34,34,35,36,27,28},
            {28,22,39,39,1,0,1,0,1,27,1,0,1,0,1,22,41,42,34,34,34,34,34,27,28},
            {28,22,0,1,0,1,0,1,0,1,0,1,0,1,0,1,34,34,34,34,34,34,34,27,28},
            {28,22,1,16,17,17,17,18,1,0,1,0,1,0,1,0,34,34,34,34,34,34,34,27,28},
            {28,33,0,16,17,17,17,18,0,27,0,1,0,1,0,22,34,34,34,34,34,34,34,31,28},
            {28,22,1,0,1,0,1,0,1,27,1,0,1,0,1,22,34,34,34,34,34,34,34,27,28},
            {28,22,0,1,0,1,0,1,0,27,0,1,0,1,0,22,34,34,34,34,34,34,34,27,28},
            {28,22,1,0,1,0,1,0,1,27,1,0,1,0,1,22,40,40,34,34,34,34,34,27,28},
            {28,25,29,29,29,29,29,29,29,26,0,1,0,1,0,25,29,29,45,29,29,29,29,26,28},
            {28,28,28,28,28,28,28,28,28,28,30,30,30,30,30,28,28,28,28,28,28,28,28,28,28},
        },
        .spawnPoints = {
            {0,10},
            {0,11},
            {0,12},
            {0,13},
            {0,14},
            {18,10},
            {18,11},
            {18,12},
            {18,13},
            {18,14}
        },
        .numberOfSpawnPoints = 10,
        .isWall = {4,5,6,9,10,11,12,14,19,20,21,22,23,24,25,26,27,29,31,32,33,44,45},
        .isWallLength = 23,
        .playerSpawnPoints = {
            {8, 10},
            {8, 11},
            {8, 12},
            {8, 13},
            {8, 14},
        },
        .playerSpawnPointSize = 5,
		.s_len = 0,
		.stops = NULL,
		.r_len = 0,
		.routes = NULL,
    };
    
    Level level_2 = {
        .number = 2,
        .map = {
            {3,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,3,3},
            {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,18,3},
            { 3,0,1,0,0,0,0,0,0,0,0,0,0,13,14,9,0,0,0,0,0,0,20,0,3 },
            { 0,0,6,6,6,6,6,0,0,4,0,0,0,16,15,8,2,0,0,0,0,0,0,0,0 },
            { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,3 },
            { 0,0,0,1,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
            { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,11,0,0,0 },
            { 3,0,0,0,1,4,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,0,0,3 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0 },
            { 3,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,3 },
            { 0,0,0,0,0,0,11,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0 },
            { 3,0,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3 },
            { 0,0,12,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0 },
            { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3 },
            { 0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0 },
            { 3,0,0,0,0,0,0,0,0,0,0,12,6,6,6,6,6,6,6,6,6,6,12,0,3 },
            { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,3 },
            { 3,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,3,3 },
        },
        .isWall = {3,6,4,13,14,15,16,8,9,12,19,20},
        .isWallLength = 12,
        .spawnPoints = {
            {0,5},
            {0,6},
            {0,11},
            {0,12},
            {0,17},
            {0,18},
            {3,0},
            {5,0},
            {7,0},
            {9,0},
            {11,0},
            {13,0},
            {15,0},
            {3,24},
            {5,24},
            {7,24},
            {9,24},
            {11,24},
            {13,24},
            {15,24},
            {18,5},
            {18,6},
            {18,11},
            {18,12},
            {18,17},
            {18,18},
        },
        .numberOfSpawnPoints = 25,
        .playerSpawnPoints = {
            {10,11},
            {10,12},
            {10,13},
            {10,14},
        },
        .playerSpawnPointSize = 4,
		.s_len = 0,
		.stops = NULL,
		.r_len = 0,
		.routes = NULL,
    };
	Level level_3 = {
		.number = 3,
		.map = {
	{ 6,6,12,6,6,6,6,10,2,2,2,2,2,0,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,6,6,6,6,6,6,8,11,3,3,3,3,1,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,4,2,2,2,2,2,9,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,5,3,3,3,3,3,23,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,6,6,22,6,6,6,8,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,6 },
	{ 6,6,6,6,6,6,6,8,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,6 },
	{ 2,2,2,2,2,2,2,9,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 3,3,3,3,3,3,3,9,7,6,6,6,6,6,6,6,6,8,7,6,6,12,6,6,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,6,6,6,6,4,2,2,2,2,2,2,2,2,2,2,2,2,2,0,6,6,19,20,6 },
	{ 6,6,6,6,6,5,3,3,3,3,3,3,3,3,3,3,3,3,3,1,6,6,8,7,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,8,7,6,6,6,8,7,6 },
	{ 6,4,2,2,2,2,2,8,7,0,6,6,6,6,6,6,6,8,23,2,2,2,21,7,6 },
	{ 6,5,3,3,3,3,3,8,7,1,6,6,6,6,6,6,6,8,9,3,3,3,3,14,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,8,7,6,6,6,6,6,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,8,7,6,6,22,6,6,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,12,6,6,6,17,18,6,6,6,6,6,6 },
	{ 6,6,6,6,6,6,6,8,7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
	},
	.isWall = { 6,22,12 },
	.isWallLength = 3,
	.spawnPoints = {
	{ 0,17 },
    { 0,18 },
    { 7,0 },
    { 8,0 },
    { 18,7 },
	{ 18,8 },
	},
	.numberOfSpawnPoints = 6,
    .playerSpawnPoints = {
        {0,12},
        {2,2},
        {11,22},
        {14,2},
        },
    .playerSpawnPointSize = 4,
	.s_len = 0,
	.stops = NULL,
	.r_len = 0,
	.routes = NULL,
	};


	Level level_4 = {
		.number = 4,
		.map = {
    { 13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 },
	{ 13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 },
	{ 13,14,3,3,3,3,3,16,13,13,14,3,3,3,3,3,3,3,3,3,3,3,16,13,13 },
	{ 13,5,0,7,8,1,2,6,13,13,5,0,0,0,0,0,11,11,11,0,0,10,6,13,13 },
	{ 13,5,0,0,0,0,0,6,13,13,5,0,0,0,0,0,0,0,0,0,0,0,6,13,13 },
	{ 13,5,0,0,0,0,0,6,13,13,5,0,0,0,0,0,0,0,0,0,0,0,6,13,13 },
	{ 21,19,0,0,0,0,0,6,13,13,5,0,0,0,14,3,3,3,16,0,0,0,6,13,13 },
	{ 22,20,0,0,0,0,0,6,13,13,5,0,0,0,6,13,13,13,5,0,0,0,6,13,13 },
	{ 13,5,0,0,0,0,0,6,13,13,5,0,0,0,6,13,13,13,5,0,0,0,6,13,13 },
	{ 13,15,4,16,0,0,0,6,13,13,5,0,0,0,6,13,13,13,5,0,0,0,6,13,13},
	{ 13,13,13,5,0,0,0,15,3,3,17,0,0,0,6,13,14,3,17,0,0,0,15,3,16},
	{ 13,13,13,5,0,0,0,10,0,0,0,0,0,0,6,13,5,9,0,0,0,0,0,0,6},
	{ 13,13,13,5,0,0,0,0,0,0,0,0,0,18,6,13,5,0,0,0,0,0,0,0,6 },
	{ 13,13,13,5,0,0,0,0,0,0,0,0,0,0,6,13,5,0,0,0,0,0,0,0,6 },
	{ 13,13,13,5,0,0,0,0,0,7,8,0,0,0,6,13,5,0,0,0,0,0,0,0,6 },
	{ 13,13,13,5,0,0,0,0,0,0,0,0,0,0,6,13,5,0,0,0,0,0,0,0,6 },
	{ 13,13,13,5,0,0,0,0,0,0,0,0,0,0,6,13,5,11,11,0,0,1,2,0,6 },
	{ 13,13,13,5,0,0,0,0,0,0,0,0,0,10,6,13,15,4,4,4,4,4,4,4,17 },
	{ 13,13,13,15,4,4,4,4,4,4,4,4,4,4,17,13,13,13,13,13,13,13,13,13,13 },
	},
	.isWall = {1,2,3,4,5,6,7,8,11,12,13,14,15,16,17,18},
	.isWallLength = 16,
	.spawnPoints = {
        {3,21},
        {6,2},
        {7,2},
        {11,7},
        {11,17},
        {17,13},
	},
	.numberOfSpawnPoints = 6,
    .playerSpawnPoints = {
        {6,2},
        {6,3},
        {7,2},
        {7,3},
    },
    .playerSpawnPointSize = 4,
	.s_len = 0,
	.stops = NULL,
	.r_len = 0,
	.routes = NULL,
	};

	
    switch (id) {
        case LEVEL_1:
            return level_1;
            break;
        case LEVEL_2:
            return level_2;
            break;
		case LEVEL_3:
			return level_3;
			break; 
		case LEVEL_4:
			return level_4;
			break;
        default:
            break;
    }
    
    return level_1;
}

static int isTileWall(Level level, int tileNumber){
    for(int i = 0; i < level.isWallLength; i++){
        if(tileNumber == level.isWall[i]){
            return 1;
        }
    }
    
    return 0;
}

Level levelManager_get_level_with_id(int id)
{
    Level level = get_level(id);
    
    SDL_Rect srcRect = {
        .x = 0,
        .y = 0,
        .w = 32,
        .h = 32
    };
    
    for(int row = 0; row < LEVEL_TILE_HEIGHT; row++){
        for(int column = 0; column < LEVEL_TILE_WIDTH; column++){
            SDL_Rect destRect = {.x = column * 32, .y = (row * 32) + 32, .w = 32,.h = 32};

            level.tile[row][column] = TileManager_createTile(level.map[row][column], isTileWall(level,level.map[row][column]), srcRect, destRect);
        }
    }
	levelManager_create_routes(&level);
    return level; 
}

Tile LevelManager_get_random_spawn_tile(Level currentLevel)
{
    int spawnPoint = rand() % currentLevel.numberOfSpawnPoints;
    
    int spawnPointX = currentLevel.spawnPoints[spawnPoint][0];
    int spawnPointY = currentLevel.spawnPoints[spawnPoint][1];
    return currentLevel.tile[spawnPointX][spawnPointY];
}

Tile LevelManager_get_random_player_spawn_tile(Level currentLevel)
{
    int spawnPoint = rand() % currentLevel.playerSpawnPointSize;
    
    int spawnPointX = currentLevel.playerSpawnPoints[spawnPoint][0];
    int spawnPointY = currentLevel.playerSpawnPoints[spawnPoint][1];
    return currentLevel.tile[spawnPointX][spawnPointY];
}

void levelManager_create_routes(Level *level)
{
	int i, j, k, l;

	for (i = 0; i < LEVEL_TILE_HEIGHT; i++) {
		for (j = 0; j < LEVEL_TILE_WIDTH; j++) {
			if (!level->tile[i][j].isWall) {
				++level->s_len;
				level->stops = (struct stop *)realloc(level->stops, level->s_len * sizeof(struct stop));
				int t = level->s_len - 1;
				level->stops[t].col = j;
				level->stops[t].row = i;
				level->stops[t].from = -1;
				level->stops[t].g = DBL_MAX;
				level->stops[t].n_len = 0;
				level->stops[t].n = NULL;
				level->tile[i][j].id = t;
			}
		}
	}
	for (i = 0; i < LEVEL_TILE_HEIGHT; i++){
		for (j = 0; j < LEVEL_TILE_WIDTH; j++) {
			if (level->tile[i][j].id >= 0) {
				for (k = i - 1; k <= i + 1; k++) {
					for (l = j - 1; l <= j + 1; l++) {
						if (((k == i) && (l == j)) || (k == -1 || l == -1)  || (k == LEVEL_TILE_HEIGHT || l == LEVEL_TILE_WIDTH)) {
							continue;
						}
						if (level->tile[k][l].id >= 0) {
							++level->r_len;
							level->routes = (struct route *)realloc(level->routes, level->r_len * sizeof(struct route));
							int t = level->r_len - 1;
							level->routes[t].x = level->tile[i][j].id;
							level->routes[t].y = level->tile[k][l].id;
							level->routes[t].d = sqrt(pow(level->stops[level->routes[t].y].row
								- level->stops[level->routes[t].x].row, 2)
								+ pow(level->stops[level->routes[t].y].col
									- level->stops[level->routes[t].x].col, 2));
							++level->stops[level->routes[t].x].n_len;
							level->stops[level->routes[t].x].n = (int*)realloc(level->stops[level->routes[t].x].n,
								level->stops[level->routes[t].x].n_len * sizeof(int));
							level->stops[level->routes[t].x].n[level->stops[level->routes[t].x].n_len - 1] = t;
						}
					}
				}
			}
		}
	}


}

Tile levelManager_get_tile_with_id(int id, Level level)
{
	for (int i = 0; i < LEVEL_TILE_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_TILE_WIDTH; j++) {
			if (level.tile[i][j].id == id) {
				return level.tile[i][j];
			}
		}
	}
	return level.tile[0][0];
}
