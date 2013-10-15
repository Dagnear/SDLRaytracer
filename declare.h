#include "gfx.h"
#include "tracer.h"

void rt_initScene();
void rt_printScene();
void rt_setCameraPosition();
void rt_setCameraDirection();
void rt_setLightCount(int count);
void rt_setObjectCount(int count);
void rt_cleanup();
void rt_setLight(int num, Light *light);
void rt_setObject(int num, Object *obj);
void rt_setResolution(int w, int h);
