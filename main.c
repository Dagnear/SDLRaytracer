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
    gfx_init(640,480,"Hello raytracer!");

    atexit(cleanup);

    rt_setResolution(640,480);
    rt_setCameraPosition(0,-10,-80);
    rt_setCameraDirection(0,0,1);
    rt_setLightCount(2);
    rt_setObjectCount(1);

    Light l1;
    l1.position.x = -80.0;
    l1.position.y = 0.0;
    l1.position.z = 0.0;
    l1.intensity = 0.80;

    Light l2;
    l2.position.x = 80.0;
    l2.position.y = 0.0;
    l2.position.z = 0.0;
    l2.intensity = 0.80;

    Object o1;
    Sphere s1;
    s1.position.x = 0.0;
    s1.position.y = 0.0;
    s1.position.z = 0.0;
    s1.radius = 30.0;
    o1.type = t_sphere;
    o1.object = &s1;

   // Object o2;
   // Sphere s2;
   // s2.position.x = 0.0;
   // s2.position.y = 0.0;
   // s2.position.z = 0.0;
   // s2.radius = 30.0;
   // o2.type = t_sphere;
   // o2.object = &s;

    rt_setLight(0,&l1);
    rt_setLight(1,&l2);
    rt_setObject(0,&o1);
    rt_printScene();

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
