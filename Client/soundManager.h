#ifndef soundManager_h
#define soundManager_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 *  @brief Init soundmanager and SDL_mixer.
 *
 */
int soundManager_init(void);

/**
 *  @brief Add a music file to memory.
 *
 *  @param pathToSound File path to sound file
 */
void soundManager_loadMusic(char *pathToSound);

/**
 *  @brief Add a "chunck" file to memory.
 *
 *  @param pathToSound File path to chunck file
 */
void soundManager_loadChunk(char *pathToSound);

/**
 *  @brief Load "die" chunck sound
 *
 *  @param pathToSound File path to die chunck file
 */
void soundManager_loadDie(char *pathToSound);

/**
 *  @brief Play loaded music
 *
 *  @param times How many times the music should repeate. 0 means forever
 */
void soundManager_playMusic(int times);

/**
 *  @brief Play loaded chunck
 *
 *  @param times How many times the music should repeate. 0 means forever
 */
void soundManager_playChunck(int times);

/**
 *  @brief Play loaded die chunck
 *
 *  @param times How many times the music should repeate. 0 means forever
 */
void soundManager_playDie(int times);

/**
 *  @brief Remove music file from mem
 *
 */
void soundManager_closeMusic(void);

/**
 *  @brief Remove chunck file from mem
 *
 */
void soundManager_closeChunk(void);

/**
 *  @brief Remove die chunck file from mem
 *
 */
void soundManager_closeDie(void);

/**
 *  @brief Quits SDL_mixer
 *
 */
void soundManager_destroy(void);

/**
 *  @brief Returns 1 if music is playing, 0 if not
 *
 */
int soundManager_isMusicPlaying(void);

/**
 *  @brief Returns 1 if music is paused, 0 if not
 *
 */
int soundManager_isMusicPaused(void);

/**
 *  @brief Pauses playing music
 *
 */
void soundManager_pauseMusic(void);

/**
 *  @brief Resumes music
 *
 */
void soundManager_resumeMusic(void);

#endif
