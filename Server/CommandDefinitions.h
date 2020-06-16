#ifndef CommandDefinitions_h
#define CommandDefinitions_h

#define SET_AVATAR_POSITION 1
#define SET_AVATAR_POSITION_FORMAT "%d %d %d %d %d"

#define REMOVE_AVATAR_FROM_WORLD 2
#define REMOVE_AVATAR_FROM_WORLD_FORMAT "%d %d"

#define INPUT_TYPE 4
#define INPUT_TYPE_FORMAT "%d"

#define GAME_INFO_TYPE 5
#define GAME_INFO_FORMAT "%d %d"

#define CLIENT_PLAYER_INFORMATION 6
#define CLIENT_PLAYER_INFORMATION_FORMAT "%d"

#define CLIENT_CONNECT_MSG_TYPE 8
#define CLIENT_CONNECT_MSG_FORMAT "%d"

#define KEY_INPUT_W 1
#define SCENE_WAITING_FOR_PLAYERS 1 
#define SCENE_LEVEL_1 2 

#define KEEP_ALIVE_MSG_TYPE 9
#define KEEP_ALIVE_MSG_FORMAT "%d"

#define DISCONNECT_MSG_TYPE 10
#define DISCONNECT_MSG_FORMAT "%d"

#define SERVER_QUIT 11

#define AVATAR_POSITION SET_AVATAR_POSITION
#define AVATAR_REMOVE REMOVE_AVATAR_FROM_WORLD
#define LOAD_NEW_MAP LOAD_NEW_MAP_TYPE
#define GAME_INFO GAME_INFO_TYPE

typedef struct{
    int type;
    int x;
    int y;
    int cat;
    int obj_id;
    int life;
    int speed;
} Avatar_position;

typedef struct{
    int type;
    int cat;
    int obj_id;
} Avatar_remove;

typedef struct{
    int type;
    int levelId;
} Load_new_map;

typedef struct{
    int type;
    int number;
} Client_status;

typedef struct{
    int type;
    int state;
    int map;
} Game_info;

typedef struct{
    int type;
    int client_id;
} Client_info;

typedef struct command{
    int type;
    Avatar_position avatar;
    Avatar_remove remove;
    Load_new_map new_map;
    Client_status status;
    Game_info game;
    Client_info client;
} Command;
/*
typedef union command{

} Command;
*/
#endif /* CommandDefinitions_h */
