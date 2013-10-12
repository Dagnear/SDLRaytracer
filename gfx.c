/*
 * SDL functions
 */
#include "gfx.h"
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

/* This is mostly from SDL 1.2 documentation */
void gfx_putPixel(int x, int y, Pixel pixel)
{
    int bpp = buffer->format->BytesPerPixel;
    /* Address to the pixel */
    Uint8 *p = (Uint8 *)buffer->pixels + y * buffer->pitch + x * bpp;

    switch(bpp)
    {
        case 1:
            *p = pixel;
        break;

        case 2:
            *(Uint16 *)p = pixel;
        break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
        break;
        
        case 4:
            *(Uint32 *)p = pixel;
        break;

        default:
            printf("[WARNING] Failed to determine correct bytes per pixel. Pixel not inserted.\n");
        break;
    }
}







