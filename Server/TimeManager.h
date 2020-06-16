#ifndef TimeManager_h
#define TimeManager_h

#include <stdio.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif

typedef struct timer {
    SDL_bool isPaused;
    SDL_bool isRunning;
    Uint32  startTicks;
    Uint32 pausedTicks;
} Timer;

typedef struct frame {
	const int FPS;
	const int frameDelay;
	Uint32 frameStart;
	//Each loop the current SDL Tick will be added to frameTime time
	int frameTime;
} Frame;

/**
 *  @brief Initialize the timer.
 *
 *  @note You have to run SDL_Init before you initialize the timer
 *
 *  @param timer The timer to initialize
 */
void timeManager_init(Timer *timer);

/**
 *  @brief Starts the timer
 *
 *  @note This should only be run once when you start the timer, if you need to pause the timer use the function timeManager_pause
 *
 *  @param timer The timer to start
 */
void timeManager_start(Timer *timer);

/**
 *  @brief Stops the timer and reset all times. Should only be run at the end of the game
 *
 *  @param timer The timer
 */
void timeManager_stop(Timer *timer);

/**
 *  @brief Pauses the timer and starts the pause clock (a clock that keeps track of how long the timer has been paused).
 *
 *  @note This will reset the start time clock, because of that it's very important that you run timeManager_unpause to start the timer again and NOT timeManager_start
 *
 *  @param timer The timer
 */
void timeManager_pause(Timer *timer);

/**
*  @brief Unpauses the timer and stops the pause clock (a clock that keeps track of how long the timer has been paused).
*
*  @param timer The timer
*/
void timeManager_unpause(Timer *timer);

/**
 *  @brief Returns the time in ms. If the game is paused it will return the pause time in ms. If the timer hasn't been started it will return 0
 *
 *  @param timer The timer
 */
Uint32 timeManager_getTime(Timer timer);

/**
*  @Brief Init the frame struct used to cap frames to a specific FPS
*
*/
Frame timeManager_frame_init(const int FPS, const int framedelay);

/**
*  @brief Caps the framerate
*
*/
void timeManager_cap_frames(Frame *frame);
#endif /* TimeManager_h */


