/*
 * SDL functions
 */
#include "gfx.h"

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

void
gfx_lockBuffer()
{
    if(SDL_MUSTLOCK(buffer))
    {
        if(SDL_LockSurface(buffer) < 0)
        {
            printf("[ERROR] Can't lock buffer: %s\n", SDL_GetError());
        }
    }
}

void
gfx_unlockBuffer()
{
    if(SDL_MUSTLOCK(buffer))
    {
        SDL_UnlockSurface(buffer);
    }
}

void gfx_fillBuffer(Pixel color)
{
    SDL_Rect r;

    r.x = 0;
    r.y = 0;
    r.w = buffer->w;
    r.h = buffer->h;

    SDL_FillRect(buffer,&r,color);
}

/* This is mostly from SDL 1.2 documentation */
void
gfx_putPixel(int x, int y, Pixel pixel)
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
            printf("[ERROR] Failed to determine correct bytes per pixel.\n");
        break;
    }
}

/* Updates buffer to screen */
void
gfx_update()
{
    if(SDL_BlitSurface(buffer,NULL,screen,NULL) < 0)
    {
        printf("[ERROR] Could not blit surface: %s\n",SDL_GetError());
    }
    SDL_Flip(screen);
}

Pixel
gfx_getPixel(int r, int g, int b)
{
    return SDL_MapRGB(buffer->format,r,g,b);
}



