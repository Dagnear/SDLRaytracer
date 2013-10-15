#include "tracer.h"
#include "gfx.h"
#include "includes.h"

Scene scene;

/* Debug function */
void
rt_printScene()
{
    int i;
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
    for(i=0;i<scene.lightCount;i++)
    {
        printf("Light[%d]: Position: x=%f y=%f z=%f Intensity %f\n",
                i,
                scene.lights[i].position.x,
                scene.lights[i].position.y,
                scene.lights[i].position.z,
                scene.lights[i].intensity);
    }

    printf("Object count %d\n",scene.objectCount);
    for(i=0;i<scene.objectCount;i++)
    {
        printf("Object[%d]: ",i);
        switch(scene.objects[i].type)
        {
            case t_null:
                printf("\tEmpty object\n");
            break;
            case t_sphere:
                printf("Sphere\n");
                Sphere *s;
                s = (Sphere *)scene.objects[i].object;
                printf("\tType: Sphere Position: x=%f y=%f z=%f Radius: %f\n",
                    s->position.x,
                    s->position.y,
                    s->position.z,
                    s->radius); 
                
            break;
            case t_plane:
            break;
            default:
                printf("unknown type %d\n",scene.objects->type);
            break;
        }
    }
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
    int i;
    scene.objectCount = count;

    if(NULL != scene.objects)
       free(scene.objects);

    scene.objects = (Object *)malloc(sizeof(Object)*count);

    for(i=0;i<count;i++)
        scene.objects[i].type = t_null;
}

void rt_cleanup()
{
    //int i;
    if(NULL != scene.lights)
        free(scene.lights);
    if(NULL != scene.objects)
    {
        /*
        for(i=0;i<scene.objectCount;i++)
        {
           if(NULL != scene.objects[i]->object)
               free(scene.objects[i]->object);
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

