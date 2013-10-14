#include "tracer.h"
#include "gfx.h"
#include "includes.h"

Scene scene;

/* Debug function */
void
printScene()
{
    printf("-=-=-Scene-=-=-\n");
    printf("Camera position: %d,%d,%d\n",
        scene.cameraPosition.x,
        scene.cameraPosition.y,
        scene.cameraPosition.z);
}

void
initScene()
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
