#ifndef TextureManager_h
#define TextureManager_h

#include <stdio.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

/**
 * @brief Get a SDL texture from a img path
 *
 * @param path The path to the image
 * @param renderer The renderer
 *
 * @return The texture
 *
 * @note This surface is freed by the function
 */
SDL_Texture* TextureManager_loadTexture(char *path, SDL_Renderer *renderer);

/**
 * @brief Copies the texture to the renderer
 *
 * @param renderer The renderer to which the texture will be draw to
 * @param texture The texture
 * @param srcRect The source rectangel
 * @param destRect The destionation rectangel, where and how big you want the texture to be draw
 *
 */
void TextureManager_drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect);
/**
*  @brief Creates a texturepath
*
*  @param obj_class The type of spritesheet to use i.e avatar or enemy
*  @param num The version of the obj_class to use i.e 1 or 2
*/
void TextureManager_create_texturepath(char *texturepath, char *obj_class, int num);
#endif /* TextureManager_h */
