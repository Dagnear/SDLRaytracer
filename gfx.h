#include "libs.h"
#include "pixel.h"

void gfx_init(int width, int height, char *title);
void gfx_cleanup();
void gfx_putPixel(int x, int y, Uint32 color);
void gfx_update();
void gfx_lockBuffer();
void gfx_unlockBuffer();
void gfx_fillBuffer(Pixel color);

/* Variables */
SDL_Surface *screen;
SDL_Surface *buffer;
