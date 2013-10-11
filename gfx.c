/*
 * SDL functions
 */
#include "includes.h"
#include "defines.h"

void
init(char *title)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL: %s\n",SDL_GetError());
        exit(1);
    }

    screen = SDL_SetVideoMode(640,480,0,SDL_HWPALETTE);

    if(screen == NULL)
    {
        printf("Could not set screen mode to 640x480 %s\n",SDL_GetError());
        exit(1);
    }

    SDL_WM_SetCaption(title,NULL);
}

void
sdl_cleanup()
{
    SDL_Quit();
}
