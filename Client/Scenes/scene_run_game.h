#ifndef scene_run_game_h
#define scene_run_game_h

#include <stdio.h>
#include "sceneManager.h"
#include "../Input.h"
#include "../world.h"

#define STATE_WAITING 1
#define STATE_RUNNING 2
#define STATE_WON 3
#define STATE_GAME_OVER 4
#define STATE_PAUSED 5

#define ESC_MENU 0
#define PLAYER_HEART 1
#define PLAYER_HEART_EMPTY 2
#define PRESS_ENTER_TO_START 3
#define PLAYER_MODEL_1 4
#define PLAYER_MODEL_2 5
#define PLAYER_MODEL_3 6
#define PLAYER_MODEL_4 7
#define GAME_WON 8
#define GAME_LOST 9

#define BUTTON_RESUME_X_START 332
#define BUTTON_RESUME_X_END 476
#define BUTTON_RESUME_Y_START 253
#define BUTTON_RESUME_Y_END 301

#define BUTTON_QUIT_X_START 332
#define BUTTON_QUIT_X_END 476
#define BUTTON_QUIT_Y_START 320
#define BUTTON_QUIT_Y_END 369
Scene scene_run_game(void);
#endif /* scene_run_game_h */
