#ifndef Pixel_h
#define Pixel_h
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "Avatar.h"
#include <stdbool.h>

void pixel_create_hitbox(Avatar *avatar, int direction);
void pixel_update_hitbox(Avatar *avatar, int direction);
bool pixel_avatar_colission(SDL_Rect a[], int a_size, SDL_Rect b[], int b_size);

#endif
