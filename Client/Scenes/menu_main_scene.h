#ifndef menu_main_scene_h
#define menu_main_scene_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <tchar.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#endif

#include <stdio.h>

#include "sceneManager.h"
#include "../TextureManager.h"

#define STATE_CONFIG 1
#define STATE_CONNECTING 2
#define STATE_ERROR_CONNECTING 3
#define STATE_JOINHOST 4
#define STATE_MAIN 5

#define BUTTON_JOIN_X_START 275
#define BUTTON_JOIN_X_END 503
#define BUTTON_JOIN_Y_START 240
#define BUTTON_JOIN_Y_END 310

#define BUTTON_H2P_X_START 337
#define BUTTON_H2P_X_END 527
#define BUTTON_H2P_Y_START 341
#define BUTTON_H2P_Y_END 399

#define BUTTON_CREDITS_X_START 250
#define BUTTON_CREDITS_X_END 434
#define BUTTON_CREDITS_Y_START 422
#define BUTTON_CREDITS_Y_END 484

#define BUTTON_EXIT_X_START 370
#define BUTTON_EXIT_X_END 570
#define BUTTON_EXIT_Y_START 518
#define BUTTON_EXIT_Y_END 576
#define BUTTON_HOST_X_START 332
#define BUTTON_HOST_X_END 476
#define BUTTON_HOST_Y_START 253
#define BUTTON_HOST_Y_END 301

#define BUTTON_JOINGAME_X_START 332
#define BUTTON_JOINGAME_X_END 476
#define BUTTON_JOINGAME_Y_START 320
#define BUTTON_JOINGAME_Y_END 369

#define BUTTON_MUTE_X_START 253
#define BUTTON_MUTE_X_END 287
#define BUTTON_MUTE_Y_START 578
#define BUTTON_MUTE_Y_END 606

#define BUTTON_PLAY_X_START 297
#define BUTTON_PLAY_X_END 331
#define BUTTON_PLAY_Y_START 578
#define BUTTON_PLAY_Y_END 606

#define SOUND_BACKGROUND 0

Scene scene_menu_main(void);
Scene scene_menu_h2p(void);
Scene scene_menu_credits(void);
Scene scene_menu_join(void);
Scene scene_menu_host(void);

#endif /* menu_main_scene_h */
