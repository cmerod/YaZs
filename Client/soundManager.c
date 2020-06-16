#include "soundManager.h"

static Mix_Music *music = NULL;
static Mix_Chunk *chunck = NULL;
static Mix_Chunk *die = NULL;

int soundManager_init()
{
    int success = 1;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2480) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = 0;
    }
    
	return success;
}

void soundManager_loadMusic(char *pathToSound)
{
    //Free and close the music before we
    if(music != NULL){
        soundManager_closeMusic();
    }
    
	music = Mix_LoadMUS(pathToSound);
	if (music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void soundManager_loadChunk(char *pathToSound)
{
    chunck = Mix_LoadWAV(pathToSound);
    if (chunck == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void soundManager_loadDie(char *pathToSound)
{
	die = Mix_LoadWAV(pathToSound);
	if (die == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void soundManager_playMusic(int times)
{
    Mix_PlayMusic(music, times);
}

void soundManager_playChunck(int times)
{
    Mix_PlayChannel(-1, chunck, times);
}

void soundManager_playDie(int times)
{
	Mix_PlayChannel(-1, die, times);
}

void soundManager_closeMusic()
{
    if(soundManager_isMusicPlaying()){
        soundManager_pauseMusic();
    }
    
    if(music != NULL){
        Mix_FreeMusic(music);
        music = NULL;
    } 
}

void soundManager_closeChunk()
{    
    if(chunck != NULL){
        Mix_FreeChunk(chunck);
        chunck = NULL;
    }
}

void soundManager_closeDie()
{
	if (die != NULL) {
		Mix_FreeChunk(die);
		die = NULL;
	}
}

void soundManager_destroy()
{
    soundManager_closeMusic();
    soundManager_closeChunk();
	Mix_Quit();
}

int soundManager_isMusicPlaying()
{
    return Mix_PlayingMusic();
}

int soundManager_isMusicPaused()
{
    return Mix_PausedMusic();
}

void soundManager_pauseMusic()
{
    if(soundManager_isMusicPlaying() || !soundManager_isMusicPaused()){
        Mix_PauseMusic();
    }
}
void soundManager_resumeMusic()
{
    if(!soundManager_isMusicPlaying() || soundManager_isMusicPaused()){
        Mix_ResumeMusic();
    }
}
