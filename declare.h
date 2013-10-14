#include "gfx.h"

void gfx_init(int width, int height, char *title);
void gfx_cleanup();
void gfx_putPixel(int x, int y, Uint32 color);
void gfx_update();
void gfx_lockBuffer();
void gfx_unlockBuffer();
Pixel gfx_getPixel(int r, int g, int b);
void gfx_fillBuffer(Pixel color);
void getInput();

void rt_initScene();
void rt_printScene();
void rt_setCameraPosition();
void rt_setCameraDirection();
