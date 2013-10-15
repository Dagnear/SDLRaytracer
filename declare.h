#include "gfx.h"
#include "tracer.h"

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
void rt_setLightCount(int count);
void rt_setObjectCount(int count);
void rt_cleanup();
void rt_setLight(int num, Light *light);
void rt_setObject(int num, Object *obj);
