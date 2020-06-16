#include "TimeManager.h"

void timeManager_init(Timer *timer)
{
    timer->isPaused = SDL_FALSE;
    timer->isRunning = SDL_FALSE;
    timer->pausedTicks = 0;
    timer->startTicks = 0;
}

void timeManager_start(Timer *timer)
{
    timer->isRunning = SDL_TRUE;
    timer->isPaused = SDL_FALSE;
    timer->pausedTicks = 0;
    timer->startTicks = SDL_GetTicks();
}

void timeManager_stop(Timer *timer)
{
    timer->isRunning = SDL_FALSE;
    timer->isPaused = SDL_FALSE;
    timer->pausedTicks = 0;
    timer->startTicks = 0;
}

void timeManager_pause(Timer *timer)
{
    if(timer->isRunning && !timer->isPaused){
        timer->isPaused = SDL_TRUE;
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
        timer->startTicks = 0;
    }
}

void timeManager_unpause(Timer *timer)
{
    if(timer->isRunning && timer->isPaused){
        timer->isPaused = SDL_FALSE;
        timer->startTicks = SDL_GetTicks() - timer->pausedTicks;
        timer->pausedTicks = 0;
    }
}

Uint32 timeManager_getTime(Timer timer)
{
    if(!timer.isRunning){
        return 0;
    }
    
    if(timer.isPaused){
        return timer.pausedTicks;
    }
    
    return SDL_GetTicks() - timer.startTicks;
}

Frame timeManager_frame_init(const int FPS, const int framedelay)
{
	Frame frame = {
		.FPS = FPS,
		.frameDelay = framedelay / FPS,
		.frameStart = 0,
		.frameTime = 0,
	};
	return frame;
}

void timeManager_cap_frames(Frame *frame)
{
	frame->frameTime = SDL_GetTicks() - frame->frameStart;
	if (frame->frameTime < frame->frameDelay) {
		SDL_Delay(frame->frameDelay - frame->frameTime);
	}
}
