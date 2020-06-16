#ifndef scene_epilogue_h
#define scene_epilogue_h

#include <stdio.h>
#include "sceneManager.h"
#include "../Client.h"
#include "../Command/commandManager.h"
#include "../Input.h"
#include "../mapManager.h"
#include "../TextureManager.h"
#include "../Enemy.h"

#define STATE_LOAD 1
#define STATE_COMPLETE 0
#define IMAGESHOWTIME 100
#define IMAGE_0 0
#define IMAGE_1 800
#define IMAGE_2 1600
#define IMAGE_3 2400

Scene scene_epilogue(void);
#endif /* scene_epilogue_h */

