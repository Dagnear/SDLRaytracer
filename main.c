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

    Light l1;
    l1.position.x = 160.0;
    l1.position.y = -150.0;
    l1.position.z = -290.0;
    l1.intensity = 0.80;

    Light l2;
    l2.position.x = -160.0;
    l2.position.y = -150.0;
    l2.position.z = -290.0;
    l2.intensity = 0.80;

    Light l3;
    l3.position.x = 0.0;
    l3.position.y = 0.0;
    l3.position.z = -500.0;
    l3.intensity = 0.0;

    Object o1;
    Sphere s1;
    s1.position.x = 60.0;
    s1.position.y = -60.0;
    s1.position.z = 0.0;
    s1.radius = 80.0;
    o1.type = t_sphere;
    o1.object = &s1;
    o1.color.r = 200;
    o1.color.g = 0;
    o1.color.b = 0;
    o1.reflection = 0.6;
    o1.transparency = 0;

    Object o2;
    Sphere s2;
    s2.position.x = -60.0;
    s2.position.y = -60.0;
    s2.position.z = 0.0;
    s2.radius = 80.0;
    o2.type = t_sphere;
    o2.object = &s2;
    o2.color.r = 200;
    o2.color.g = 0;
    o2.color.b = 0;
    o2.reflection = 0.2;
    o2.transparency = 0;

    Object o3;
    Sphere s3;
    s3.position.x = 0.0;
    s3.position.y = 60.0;
    s3.position.z = 0.0;
    s3.radius = 80.0;
    o3.type = t_sphere;
    o3.object = &s3;
    o3.color.r = 200;
    o3.color.g = 0;
    o3.color.b = 0;
    o3.reflection = 0.0;
    o3.transparency = 0;

    Object o4;
    Plane p1;
    p1.position.x = 0.0;
    p1.position.y = 0.0;
    p1.position.z = 100.0;
    p1.normal.x = 0.0;
    p1.normal.y = 0.0;
    p1.normal.z = -1.0;
    o4.type = t_plane;
    o4.object = &p1;
    o4.color.r = 0;
    o4.color.g = 200;
    o4.color.b = 0;
    o4.reflection = 0.4;
    o4.transparency = 0;

    Object o5;
    Plane p2;
    p2.position.x = 0.0;
    p2.position.y = 80.0;
    p2.position.z = 0.0;
    p2.normal.x = 0.0;
    p2.normal.y = -1.0;
    p2.normal.z = 0.0;
    o5.type = t_plane;
    o5.object = &p2;
    o5.color.r = 100;
    o5.color.g = 100;
    o5.color.b = 100;
    o5.reflection = 0.0;
    o5.transparency = 0;

    rt_setResolution(640,480);
    rt_setFov(90);
    rt_setCameraPosition(0,0,-100);
    rt_setCameraDirection(0,0,1);
    rt_setLightCount(3);
    rt_setObjectCount(5);

    rt_setLight(0,&l1);
    rt_setLight(1,&l2);
    rt_setLight(2,&l3);
    rt_setObject(0,&o1);
    rt_setObject(1,&o2);
    rt_setObject(2,&o3);
    rt_setObject(3,&o4);
    rt_setObject(4,&o5);
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
