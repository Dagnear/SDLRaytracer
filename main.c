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
    printf("sizeof(long double) = %lu,sizeof(double) = %lu, sizeof(float) = %lu\n",
        sizeof(long double),sizeof(double),sizeof(float));

    rt_initScene();
    gfx_init(640,480,"Hello raytracer!");

    atexit(cleanup);

    rt_setResolution(640,480);
    rt_setCameraPosition(0,0,-100);
    rt_setCameraDirection(0,0,1);
    rt_setLightCount(2);
    rt_setObjectCount(2);

    Light l1;
    l1.position.x = -140.0;
    l1.position.y = -140.0;
    l1.position.z = -140.0;
    l1.intensity = 0.80;

    Light l2;
    l2.position.x = 90.0;
    l2.position.y = 90.0;
    l2.position.z = -20.0;
    l2.intensity = 0.80;

    Object o1;
    Sphere s1;
    s1.position.x = 0.0;
    s1.position.y = 0.0;
    s1.position.z = 0.0;
    s1.radius = 80.0;
    o1.type = t_sphere;
    o1.object = &s1;
    o1.color.r = 170;
    o1.color.g = 120;
    o1.color.b = 0;

    Object o2;
    Sphere s2;
    s2.position.x = -90.0;
    s2.position.y = -90.0;
    s2.position.z = -90.0;
    s2.radius = 7.0;
    o2.type = t_sphere;
    o2.object = &s2;
    o2.color.r = 255;
    o2.color.g = 0;
    o2.color.b = 0;

    rt_setLight(0,&l1);
    rt_setLight(1,&l2);
    rt_setObject(0,&o1);
    rt_setObject(1,&o2);
    rt_printScene();

    Pixel p[640*480];
    rt_renderScene(&p);
    //Pixel yellow = gfx_createPixel(255,255,0);
    //Pixel blue = gfx_createPixel(0,0,255);

    gfx_lockBuffer();
    //gfx_fillBuffer(blue);
    
    int x,y;
    for(y=0;y<480;y++)
    {
        for(x=0;x<640;x++)
        {
            gfx_putPixel(x,y,p[y*640+x]);
        }
    }
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
