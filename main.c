/*
 * Minimalistic raytracer
 */
#include "includes.h"
#include "declare.h"

void
cleanup()
{
    gfx_cleanup();
}

int
main(int argc, char **argv)
{
    int run;

    printf("Hello raytracer\n");

    rt_initScene();
    rt_setCameraPosition(10,20,30);
    rt_setCameraDirection(-1,0,1);
    rt_setLightCount(2);
    rt_setObjectCount(3);
    rt_printScene();

    gfx_init(640,480,"Hello raytracer!");
    atexit(cleanup);

    Pixel yellow = gfx_getPixel(255,255,0);
    Pixel blue = gfx_getPixel(0,0,255);

    gfx_lockBuffer();
    gfx_fillBuffer(blue);
    gfx_putPixel(50,50,yellow);
    gfx_unlockBuffer();
    gfx_update();

    run = 1;
    while(1 == run)
    {
        getInput();
        SDL_Delay(16);
    }

    return 0;
}
