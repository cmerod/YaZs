#include "TextureManager.h"
#pragma warning(disable : 4996)

SDL_Texture* TextureManager_loadTexture (char *path, SDL_Renderer *renderer)
{
    SDL_Surface *tempSurface = IMG_Load(path);
    
    if(tempSurface == NULL){
        printf("Could not load image: %s, SDL Error: %s\n",path, SDL_GetError());
        return NULL;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return texture;
}

void TextureManager_drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void TextureManager_create_texturepath(char *texturepath, char *obj_class, int num)
{
	char number[10] = { 0 };
	sprintf(number, "%d", num);
	strcpy(texturepath, "Graphics/");
	strcat(texturepath, obj_class);
	strcat(texturepath, number);
	strcat(texturepath, ".png");
}

