/*
 * Minimalistic raytracer
 */
#include "gfx.h"
#include "tracer.h"
#include "input.h"
#include "pixel.h"

void
cleanup()
{
    gfx_cleanup();
    rt_cleanup();
}

int
main(int argc, char **argv)
{
    int run;

    printf("Hello raytracer\n");

    rt_initScene();
    rt_setResolution(640,480);
    rt_setCameraPosition(10,20,30);
    rt_setCameraDirection(-1,0,1);
    rt_setLightCount(2);
    rt_setObjectCount(3);

    Light l;
    l.position.x = 10.0;
    l.position.y = 0.0;
    l.position.z = -100.0;
    l.intensity = 0.80;

    Object o;
    Sphere s;
    s.position.x = 1.0;
    s.position.y = 2.0;
    s.position.z = 3.0;
    s.radius = 20.0;
    o.type = t_sphere;
    o.object = &s;

    rt_setLight(0,&l);
    rt_setObject(0,&o);
    rt_printScene();

    gfx_init(640,480,"Hello raytracer!");
    atexit(cleanup);

    Pixel yellow = gfx_createPixel(255,255,0);
    Pixel blue = gfx_createPixel(0,0,255);

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
