#include <math.h>
#include "libs.h"
#include "tracer.h"
#include "gfx.h"

#define EPSILON 0.01
#define BIAS 0.0001
#define MAXRECURSION 3

Scene scene;

/* Debug function */
void
rt_printScene()
{
    int i;
    printf("-=-=-=-Scene-=-=-=-\n");
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

    printf("\n-=-=-=-Vector math test-=-=-=-\n");
    Vector v1,v2,v3; double scalar, result, len;
    v1.x = 4.0;   v2.x = 8.0;   v3.x = 0.0;
    v1.y = 3.0;   v2.y = 1.0;   v3.y = 0.0;
    v1.z = 9.0;   v2.z = -3.4; v3.z = 0.0;
    scalar = 5.0;

    printf("v1 = (%f,%f,%f)\n",v1.x,v1.y,v1.z);
    printf("v2 = (%f,%f,%f)\n",v2.x,v2.y,v2.z);

    len = rt_vectorLength(&v1);
    printf("length(v1) = %f\n",len);

    rt_vectorAdd(&v1,&v2,&v3);
    printf("v1 + v2 = (%f,%f,%f)\n",v3.x,v3.y,v3.z);

    rt_vectorSubstract(&v1,&v2,&v3);
    printf("v1 - v2 = (%f,%f,%f)\n",v3.x,v3.y,v3.z);

    rt_vectorMultiply(&v1,scalar,&v3);
    printf("v1 * %f = (%f,%f,%f)\n",scalar,v3.x,v3.y,v3.z);

    result = rt_dotProduct(&v1,&v2);
    printf("dot(v1,v2) = %f\n",result);

    rt_vectorNormalize(&v1,&v3);
    printf("normalize(v1) = (%f,%f,%f)\n",v3.x,v3.y,v3.z);

    printf("\n-=-=-=-Intersection testing-=-=-=-\n");
    Ray r; Object o; Sphere s; Vector n, p; double intersects;
    r.position.x = -10.0;     r.direction.x = 0.0; s.position.x = 0.0;
    r.position.y = 5.0;    r.direction.y = 0.0; s.position.y = 0.0;
    r.position.z = -80.0;   r.direction.z = 1.0; s.position.z = 0.0;
    s.radius = 30.0;
    o.type = t_sphere; o.object = &s;
    rt_vectorNormalize(&r.direction,&r.direction);

    printf("Intersection of\n");
    printf("\t[RAY] Position: (%f,%f,%f) Direction: (%f,%f,%f)\n",
        r.position.x,r.position.y,r.position.z,
        r.direction.x,r.direction.y,r.direction.z);
    printf("\t[SPHERE] Position: (%f,%f,%f) Radius: %f\n",
        s.position.x,s.position.y,s.position.z, s.radius);

    intersects = rt_intersect(&r,&o);
    printf("Result: %f\n",intersects);

    printf("\n-=-=-=-Trace testing-=-=-=-\n");
    rt_trace(&r,MAXRECURSION);

    printf("\n_______END OF DEBUG_______\n");
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

    scene.objectCount = 0; scene.objects = NULL;
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

    /* Normalize direction vector */
    rt_vectorNormalize(&scene.cameraDirection,&scene.cameraDirection);
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
 * Vector math functions
 */
void rt_vectorSubstract(Vector *v1, Vector *v2, Vector *result)
{
    result->x = (v1->x) - (v2->x);
    result->y = (v1->y) - (v2->y);
    result->z = (v1->z) - (v2->z);
}

void rt_vectorAdd(Vector *v1, Vector *v2, Vector *result)
{
    result->x = (v1->x) + (v2->x);
    result->y = (v1->y) + (v2->y);
    result->z = (v1->z) + (v2->z);
}

void rt_vectorMultiply(Vector *v1, double scalar, Vector *result)
{
    result->x = v1->x*scalar;
    result->y = v1->y*scalar;
    result->z = v1->z*scalar;
}

double rt_dotProduct(Vector *v1, Vector *v2)
{
    double v1x,v1y,v1z,v2x,v2y,v2z;
    double rx,ry,rz;
    v1x = v1->x; v1y = v1->y; v1z = v1->z;
    v2x = v2->x; v2y = v2->y; v2z = v2->z;

    rx = v1x*v2x; ry = v1y*v2y; rz = v1z*v2z;
   // printf("[DEBUG] Dot product:\n");
   // printf("\tv1x = %f, v2x = %f v1x*v2x = %f\n",v1x,v2x,rx);
   // printf("\tv1y = %f, v2y = %f v1y*v2y = %f\n",v1y,v2y,ry);
   // printf("\tv1z = %f, v2z = %f v1z*v2z = %f\n",v1z,v2z,rz);
   // printf("\tv1x*v2x + v1y*v2y + v1z*v2z = %f\n",rz+ry+rz);
    return rx + ry + rz; 
}

double rt_vectorLength(Vector *v)
{
    double x,y,z;
    x = v->x; y = v->y; z = v->z;
    return sqrt((x*x) + (y*y) + (z*z));
}

void rt_vectorNormalize(Vector *v,Vector *result)
{
    double len,x,y,z;
    
    len = rt_vectorLength(v);
    x = (v->x)/len;
    y = (v->y)/len;
    z = (v->z)/len;

    result->x = x;
    result->y = y;
    result->z = z;
}

/* Determine surface normal for object base on point hit */
void rt_surfaceNormal(Object *object, Vector *pointHit, Vector *normalHit)
{
    switch(object->type)
    {
        case t_sphere:
        {
            Sphere *s = (Sphere *)object->object;
            rt_vectorSubstract(pointHit,&(s->position),normalHit);
            rt_vectorNormalize(normalHit,normalHit);
        } break;
        default:
            printf("[WARNING] Tried to calculate surface normal of unkown object type: %d\n",object->type);
        break;
    }
}

/*
 * Determine intersection scalar with object if any
 */
double rt_intersect(Ray *ray,Object *object)
{
    switch(object->type)
    {
        case t_sphere:
        {
            Sphere *s = (Sphere *)object->object;
            /* Sphere is assumed at origin and direction
             * vector of the ray to be normalized to allow
             * some optimization of the quadratic intersection
             * equation
             */
            Vector distance; double B, D, t, radius2;

            rt_vectorSubstract(&(ray->position),&(s->position),&distance);

            B = rt_dotProduct(&(ray->direction),&distance);
            
            printf("[DEBUG] Distance (%f,%f,%f) RayDirection dot Distance = %f\n",
                distance.x,distance.y,distance.z,B);
            /* Ray direction is not going towards origo */
            //if(B < 0.0) return 0.0;
            
            //D = rt_dotProduct(&distance,&distance) - B*B;
            radius2 = (s->radius)*(s->radius);
            D = B*B - rt_dotProduct(&(ray->direction),&(ray->direction)) * (rt_dotProduct(&distance,&distance) - radius2);
            printf("[DEBUG] D = %f, B = %f\n",D,B);

            /* No real roots, no intersection */
            //if(D > radius2) return 0.0;
            //D = sqrt(radius2-D);
            if(D < 0.0) return 0.0;
            else D = sqrt(D);
            printf("[DEBUG] t0 = %f, t1 = %1f\n",
                (-B-D)/rt_dotProduct(&(ray->direction),&(ray->direction)),
                (-B+D)/rt_dotProduct(&(ray->direction),&(ray->direction)));

            /* Smaller root first */
            t = (- B - D)/rt_dotProduct(&(ray->direction),&(ray->direction));
            if(t < 0.0) t = (-B + D)/rt_dotProduct(&(ray->direction),&(ray->direction));
            if(t < 0.0) return 0.0;

            /* t is not too close or behind the viewpoint */
            return t;

           // /* Calculate point hit */
           // rt_vectorMultiply(&normalizedDirection,t,&resultVector);
           // rt_vectorAdd(&resultVector,&(ray->position),pointHit);

           // /* Calculate surface normal of the point hit */
           // rt_vectorSubstract(pointHit,&(s->position),normalHit);

        } break;
        default:
            printf("[WARNING] Tried to calculate intersection for unkown object type: %d\n",object->type);
        break;
    }

    /* We do not know how to calculate intersection 
     * for unkown object
     */
    return 0.0;    
}

double rt_illumination(Vector *pointHit, Vector *normalHit)
{
    Ray shadowRay; int inShadow, i,j;
    double brightness, lightDistance, t, dot;
    Vector light, bias;

    shadowRay.position.x = pointHit->x;
    shadowRay.position.y = pointHit->y;
    shadowRay.position.z = pointHit->z;

    /* Adding some bias to avoid precision errors */
    rt_vectorMultiply(normalHit,BIAS,&bias);
    rt_vectorAdd(&(shadowRay.position),&bias,&(shadowRay.position));

    brightness = 0.0;
    for(i=0;i<scene.lightCount;i++)
    {
        light.x = scene.lights[i].position.x;
        light.y = scene.lights[i].position.y;
        light.z = scene.lights[i].position.z;
        printf("[DEBUG] Light position (%f,%f,%f)\n",light.x,light.y,light.z);

        rt_vectorSubstract(&(light),&(shadowRay.position),&(shadowRay.direction));
        lightDistance =  rt_vectorLength(&(shadowRay.direction));
        rt_vectorNormalize(&(shadowRay.direction),&(shadowRay.direction));

        printf("[DEBUG] Shadow ray position(%f,%f,%f) direction(%f,%f,%f)\n",
            shadowRay.position.x,shadowRay.position.y,shadowRay.position.z,
            shadowRay.direction.x,shadowRay.direction.y,shadowRay.direction.z);
        printf("\tLight distance %f\n",lightDistance);
        dot = rt_dotProduct(normalHit,&(shadowRay.direction));
        printf("\tDot = %f\n",dot);

        inShadow = 0;
        for(j=0;j<scene.objectCount;j++)
        {
            printf("[DEBUG] Intersection with objects[%d]\n",j);
            t = rt_intersect(&shadowRay,&(scene.objects[j])); 
            if(t > 0.0 && t < lightDistance)
                inShadow = 1;

            printf("\tt=%f inShadow=%d\n",t,inShadow);
        }

        if(0 == inShadow)
            brightness += scene.lights[i].intensity;
    }

    return brightness;
}

/* Trace a color for single ray */
Pixel rt_trace(Ray *ray, int recursions)
{
    Object *object;
    Vector pointHit, normalHit;
    double minDist, t; int i,j;

    object = NULL;
    minDist = INFINITY;
    
    /* Find out closest intersection, if any */
    for(i=0;i<scene.objectCount;i++)
    {
        t = rt_intersect(ray,&(scene.objects[i]));
        if(t > 0.0 && t < minDist)
        {
            minDist = t;
            object = &scene.objects[i];
            printf("[DEBUG] Minimum distance updated to: %f\n",minDist);
        }
    }
    if(NULL == object) printf("[DEBUG] No object intersects\n");
    /* If there was an intersection */
    if(NULL != object)
    {
        double brightness;

        /* Calculate point hit */
        rt_vectorMultiply(&(ray->direction),minDist,&pointHit);
        rt_vectorAdd(&pointHit,&(ray->position),&pointHit);

        /* Calculate normal hit */
        rt_surfaceNormal(object,&pointHit,&normalHit);

        printf("[DEBUG] Point hit(%f,%f,%f) Normal hit(%f,%f,%f)\n",
            pointHit.x,pointHit.y,pointHit.z,
            normalHit.x,normalHit.y,normalHit.z);

        brightness = rt_illumination(&pointHit,&normalHit);

        printf("[DEBUG] Got brightness %f\n",brightness);

        /* Placeholder for color support */
        if(brightness > 0)
            return gfx_createPixel(255,0,0);
    }
    
    /* No object was hit */
    return gfx_createPixel(0,0,0);
}

/* 
 * Trace for each pixel and store resulting
 * color in an array
 * */
void rt_renderScene(Pixel *pixels)
{
    int x,y;
    Ray primaryRay;

    primaryRay.direction.x = scene.cameraDirection.x;
    primaryRay.direction.y = scene.cameraDirection.y;
    primaryRay.direction.z = scene.cameraDirection.z;

    primaryRay.position.y = scene.cameraPosition.y - (scene.screenY/2);
    primaryRay.position.z = scene.cameraPosition.z;

    for(y=0;y<scene.screenY;y++)
    {
        primaryRay.position.x = scene.cameraPosition.x - (scene.screenX/2);
        for(x=0;x<scene.screenX;x++)
        {
            pixels[y*scene.screenX+x] = rt_trace(&primaryRay,MAXRECURSION);
            primaryRay.position.x += 1;
        }
        primaryRay.position.y += 1;
    }
}
