/*
 * SDL functions
 */
#include "includes.h"
#include "defines.h"

void
gfx_init(int width, int height, char *title)
{
    /* Initialize SDL */
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("[ERROR] Could not initialize SDL: %s\n",SDL_GetError());
        exit(1);
    }

    /* Initialize window */
    screen = SDL_SetVideoMode(width,height,0,SDL_HWPALETTE);

    if(NULL == screen)
    {
        printf("[ERROR] Could not set screen mode to 640x480 %s\n",SDL_GetError());
        exit(1);
    }

    /* Initialize buffer */
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height,
                screen->format->BitsPerPixel,
                screen->format->Rmask,
                screen->format->Gmask,
                screen->format->Bmask,
                screen->format->Amask
            );

    if(NULL == buffer)
    {
        printf("[ERROR] Could not initialize buffer %s\n",SDL_GetError());
    }
                
    SDL_WM_SetCaption(title,NULL);
}

void
gfx_cleanup()
{
    SDL_FreeSurface(buffer);
    SDL_FreeSurface(screen);
    SDL_Quit();
}
