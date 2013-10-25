#include "pixel.h"
#include "gfx.h"

Pixel
gfx_createPixel(int r, int g, int b)
{
    return SDL_MapRGB(buffer->format,r,g,b);
}

