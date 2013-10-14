#include "tracer.h"
#include "gfx.h"
#include "includes.h"

Scene scene;

/* Debug function */
void
rt_printScene()
{
    printf("-=-=-Scene-=-=-\n");
    printf("Camera position: %d,%d,%d\n",
        scene.cameraPosition.x,
        scene.cameraPosition.y,
        scene.cameraPosition.z);
    printf("Camera direction: %d,%d,%d\n",
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
