
// Categories of objects
#define PLAYER 1
#define ENEMY 2
#define ATTACK 3

// Input.h
#define NUM_OF_KEYS 100
#define ESC 0
#define W 1
#define A 2
#define S 3
#define D 4
#define SPACE 5
#define ENTER 6

// Game.h
#define SCREEN_W 800
#define SCREEN_H 640
#define SCREEN_SCALE 1
#define SCREEN_NAME "YaZs"

// Client.h
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

// mapManager.h
#define LEVEL_1_NUM_TEXTURES 39
#define LEVEL_2_NUM_TEXTURES 17
#define LEVEL_3_NUM_TEXTURES 24
#define LEVEL_4_NUM_TEXTURES 3
#define LEVEL_MAX_NUM_TEXTURES 50 //How many textures each level has

// levelMananger.h
#define LEVEL_TILE_WIDTH 25
#define LEVEL_TILE_HEIGHT 19
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4

// Player.h
#define FRAME_COUNT 8
#define FRAME_ATTACK 2
#define ATTACK_SPEED 200
#define ANIM_DOWN	0
#define ANIM_LEFT	32
#define ANIM_UP		64
#define ANIM_RIGHT	96
#define ANIM_1		0
#define ANIM_2		32
#define ANIM_3		64
#define ANIM_4		96
#define MOVING		0
#define STATIONARY	3
#define ATTACKING	1
#define DYING		2
#define VERTICAL ANIM_DOWN
#define LATERAL ANIM_LEFT
#define INVUL_TIME  1

// World.h
#define MAX_PLAYERS 4
#define MAX_ENEMIES 50
#define START_LIFE_PLAYER 3
#define LIFE_ENEMY 1
#define SPEED_PLAYER 3
#define SPEED_ENEMY 1
#define RECT_H	32
#define RECT_W	32

#define SET_PLAYER_POSITION 1 

//Server
#define STATE_WAIT 1
#define STATE_RUN 2
#define STATE_WIN 3
#define STATE_LOST 4
#define ROUND_LEN 30  //Change length of a round
