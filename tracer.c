#include "libs.h"
#include "tracer.h"
#include "gfx.h"

#define EPSILON 0.01
#define MAXRECURSION 3

Scene scene;

/* Debug function */
void
rt_printScene()
{
    int i;
    printf("-=-=-Scene-=-=-\n");
    printf("Resolution: %dx%d\n",scene.screenX,scene.screenY);
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
            {
                printf("Empty object\n");
            } break;
            case t_sphere:
            {
                printf("Sphere\n");
                Sphere *s;
                s = (Sphere *)scene.objects[i].object;
                printf("\tType: Sphere Position: x=%f y=%f z=%f Radius: %f\n",
                    s->position.x,
                    s->position.y,
                    s->position.z,
                    s->radius); 
                
            } break;
            case t_plane:
            {
                printf("\tType: Plane No features implemented.\n");
            } break;
            default:
            {
                printf("unknown type %d\n",scene.objects->type);
            } break;
        }
    }

    printf("\n+-+-+-Vector math test-+-+-+\n");
    Vector v1,v2,v3; float scalar, result;
    v1.x = 4.0;   v2.x = 8.0;   v3.x = 0.0;
    v1.y = 3.0;   v2.y = 1.0;   v3.y = 0.0;
    v1.z = 9.0;   v2.z = -3.4; v3.z = 0.0;
    scalar = 5.0;

    printf("v1 = (%f,%f,%f)\n",v1.x,v1.y,v1.z);
    printf("v2 = (%f,%f,%f)\n",v2.x,v2.y,v2.z);

    rt_vectorAdd(&v1,&v2,&v3);
    printf("v1 + v2 = (%f,%f,%f)\n",v3.x,v3.y,v3.z);

    rt_vectorSubstract(&v1,&v2,&v3);
    printf("v1 - v2 = (%f,%f,%f)\n",v3.x,v3.y,v3.z);

    rt_vectorMultiply(&v1,scalar,&v3);
    printf("v1 * %f = (%f,%f,%f)\n",scalar,v3.x,v3.y,v3.z);

    result = rt_dotProduct(&v1,&v2);
    printf("dot(v1,v2) = %f\n",result);

    printf("\n-_-_-_Intersection testing_-_-_-\n");
    Ray r; Object o; Sphere s; Vector n, p; int intersects;
    r.position.x = 10.0; r.direction.x = 1.0; s.position.x = -20.0;
    r.position.y = 20.0; r.direction.y = 1.0; s.position.y = 15.0;
    r.position.z = 30.0; r.direction.z = 1.0; s.position.z = 4.0;
    s.radius = 5;
    o.type = t_sphere; o.object = &s;
    intersects = rt_intersect(&r,&o,&n,&p);
    printf("Intersection of\n");
    printf("\t[RAY] Position: (%f,%f,%f) Direction: (%f,%f,%f)\n",
        r.position.x,r.position.y,r.position.z,
        r.direction.x,r.direction.y,r.direction.z);
    printf("\t[SPHERE] Position: (%f,%f,%f) Radius: %f\n",
        s.position.x,s.position.y,s.position.z, s.radius);
    printf("Result: %d\n",intersects);

}

void
rt_initScene()
{
    scene.screenX = 0;
    scene.screenY = 0;

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
rt_setResolution(int w, int h)
{
    scene.screenX = w;
    scene.screenY = h;
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

/*
 * Trace a single ray
 * limit for recursion
 */
Pixel rt_trace(Ray *primaryRay, int limit)
{
    //Foo
    return 0;
}

/*
 * Renders the scene
 */
void rt_renderScene()
{
    int x,y;
    Pixel pixel;
    Ray ray;

    ray.position.x = scene.cameraPosition.x - (scene.screenX/2);
    ray.position.y = scene.cameraPosition.y - (scene.screenY/2);
    ray.position.z = scene.cameraPosition.z;

    for(y=0;y<scene.screenY;y++)
    {
        for(x=0;x<scene.screenX;x++)
        {
            pixel = rt_trace(&ray,0);
            gfx_putPixel(x,y,pixel);
        }
    }
}

/*
 * Vector math functions
 */
void rt_vectorSubstract(Vector *v1, Vector *v2, Vector *result)
{
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
}

void rt_vectorAdd(Vector *v1, Vector *v2, Vector *result)
{
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

void rt_vectorMultiply(Vector *v1, float scalar, Vector *result)
{
    result->x = v1->x*scalar;
    result->y = v1->y*scalar;
    result->z = v1->z*scalar;
}

float rt_dotProduct(Vector *v1, Vector *v2)
{
    return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z; 
}

/*
 * Determine intersection with object if any
 */
int rt_intersect(Ray *ray,Object *object,Vector *pointHit,Vector *normalHit)
{
    switch(object->type)
    {
        case t_sphere:
        {
            Sphere *s = (Sphere *)object->object;
            /* Let's assume sphere is in origin */
            Vector distance;
            rt_vectorSubstract(&(s->position),&(ray->position),&distance);
            printf("Distance: (%f,%f,%f)\n",distance.x,distance.y,distance.z);
        } break;
        default:
        break;
    }

    /* No intersection */
    return 0;    
}


