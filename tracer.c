#include "tracer.h"
#include "gfx.h"
#include "includes.h"

Scene scene;

/* Debug function */
void
rt_printScene()
{
    printf("-=-=-Scene-=-=-\n");
    printf("Camera position: %f,%f,%f\n",
        scene.cameraPosition.x,
        scene.cameraPosition.y,
        scene.cameraPosition.z);
    printf("Camera direction: %f,%f,%f\n",
        scene.cameraDirection.x,
        scene.cameraDirection.y,
        scene.cameraDirection.z);
    printf("Light count %d\n",scene.lightCount);
    printf("Object count %d\n",scene.objectCount);
}

void
rt_initScene()
{
    scene.cameraPosition.x = 0;
    scene.cameraPosition.y = 0;
    scene.cameraPosition.z = 0;

    scene.cameraDirection.x = 0;
    scene.cameraDirection.y = 0;
    scene.cameraDirection.z = 0;

    scene.lightCount = 0;
    scene.lights = NULL;

    scene.objectCount = 0;
    scene.objects = NULL;
}

void
rt_setCameraPosition(int x, int y, int z)
{
    scene.cameraPosition.x = x;
    scene.cameraPosition.y = y;
    scene.cameraPosition.z = z;
}

void
rt_setCameraDirection(int x, int y, int z)
{
    scene.cameraDirection.x = x;
    scene.cameraDirection.y = y;
    scene.cameraDirection.z = z;
}

void rt_setLightCount(int count)
{
    scene.lightCount = count; 

    if(NULL != scene.lights)
       free(scene.lights);

    scene.lights = (Light *)malloc(sizeof(Light)*count);
}

void rt_setObjectCount(int count)
{
    scene.objectCount = count;

    if(NULL != scene.objects)
       free(scene.objects);

    scene.objects = (Object *)malloc(sizeof(Object)*count);
}

void rt_cleanup()
{
    int i;
    if(NULL != scene.lights)
        free(scene.lights);
    if(NULL != scene.objects)
    {
        /*
        for(i=0;i<scene.objectCount;i++)
        {
           if(NULL != scene.objects[i].object)
               free(scene.objects[i].object);
        }
        */
        free(scene.objects);
    }
    
}

void rt_setLight(int num, Light *light)
{
    if(scene.lightCount > num)
    {
        scene.lights[num].position.x = light->position.x;
        scene.lights[num].position.y = light->position.y;
        scene.lights[num].position.z = light->position.z;
        scene.lights[num].intensity = light->intensity;
    }
    else
    {
        printf("[WARNING] Tried to assign light out of bounds\n");
    }
}

void rt_setObject(int num, Object *obj)
{
    if(scene.objectCount > num)
    {
        scene.objects[num].type = obj->type;
        scene.objects[num].object = obj->object;
    }
    else
    {
        printf("[WARNING] Tried to assign object out of bounds\n");
    }
}

