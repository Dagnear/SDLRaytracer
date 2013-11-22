#include <math.h>
#include "libs.h"
#include "tracer.h"
#include "gfx.h"

#define EPSILON 0.01
#define BIAS 0.0001
#define MAXRECURSION 3

Scene scene;

/* Debug function 
 * prints out results of tests */
void
rt_printScene()
{
    int i;
    printf("-=-=-=-Scene-=-=-=-\n");
    printf("Resolution: %dx%d\n",scene.screenX,scene.screenY);
    printf("Field of View: %d\n",scene.fov);
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
    Ray r; Object o; Sphere s; double intersects;
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

/* 
 * Initializes variable with 
 * zero or NULL values
 */
void
rt_initScene()
{
    scene.screenX = 0;
    scene.screenY = 0;

    scene.fov = 0;

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

/*
 * Set resultin resolution of the scene
 * "render"
 */
void
rt_setResolution(int w, int h)
{
    scene.screenX = w;
    scene.screenY = h;
}

/*
 * Sets field of view angle
 * in degrees
 */
void
rt_setFov(int fov)
{
    scene.fov = fov;
}

/*
 * Sets camera (viewpoin) location
 */
void
rt_setCameraPosition(int x, int y, int z)
{
    scene.cameraPosition.x = x;
    scene.cameraPosition.y = y;
    scene.cameraPosition.z = z;
}

/*
 * Sets direction of the camera
 * (to which direction we are looking)
 */
void
rt_setCameraDirection(int x, int y, int z)
{
    scene.cameraDirection.x = x;
    scene.cameraDirection.y = y;
    scene.cameraDirection.z = z;

    /* Normalize direction vector */
    rt_vectorNormalize(&scene.cameraDirection,&scene.cameraDirection);
}

/*
 * Allocates enough space for specified amount
 * of lights in the scene
 */
void rt_setLightCount(int count)
{
    scene.lightCount = count; 

    if(NULL != scene.lights)
       free(scene.lights);

    scene.lights = (Light *)malloc(sizeof(Light)*count);
}

/*
 * Allocates enough space for specified amount of
 * objects in the scene
 */
void rt_setObjectCount(int count)
{
    int i;
    scene.objectCount = count;

    if(NULL != scene.objects)
       free(scene.objects);

    scene.objects = (Object *)malloc(sizeof(Object)*count);

    for(i=0;i<count;i++)
    {
        scene.objects[i].type = t_null;
        scene.objects[i].color.r = 0;
        scene.objects[i].color.g = 0;
        scene.objects[i].color.b = 0;
        scene.objects[i].reflection = 0;
        scene.objects[i].transparency = 0;
    }
}

/*
 * Frees space allocated for objects and lights
 *
 * TODO: After implementing placement of the objects
 * add free routine. Lights are always placed on
 * stack (for now).
 */
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

/*
 * Copies properties from light pointer
 * to specified light in scene. In stack.
 */
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

/*
 * Copies properties of the object to corresponding
 * object in stack.
 *
 * TODO: Should there be special handler for different
 * shapes or should they be handled otherwise?
 */
void rt_setObject(int num, Object *obj)
{
    if(scene.objectCount > num)
    {
        scene.objects[num].type = obj->type;
        scene.objects[num].object = obj->object;
        scene.objects[num].color.r = obj->color.r;
        scene.objects[num].color.g = obj->color.g;
        scene.objects[num].color.b = obj->color.b;
        scene.objects[num].reflection = obj->reflection;
        scene.objects[num].transparency = obj->transparency;

        //If object needs special handler
        switch(obj->type)
        {
            case t_plane:
            {
                Plane *p = (Plane *)obj->object;
                rt_vectorNormalize(&(p->normal),&(p->normal));
            } break;
            default:
            break;
        }
    }
    else
    {
        printf("[WARNING] Tried to assign object out of bounds\n");
    }
}

/*
 * Vector math function
 * Substract v1 from v2 and store in result
 */
void rt_vectorSubstract(Vector *v1, Vector *v2, Vector *result)
{
    result->x = (v1->x) - (v2->x);
    result->y = (v1->y) - (v2->y);
    result->z = (v1->z) - (v2->z);
}

/*
 * Vector math function
 * Add v1 to v2 and store in result
 */
void rt_vectorAdd(Vector *v1, Vector *v2, Vector *result)
{
    result->x = (v1->x) + (v2->x);
    result->y = (v1->y) + (v2->y);
    result->z = (v1->z) + (v2->z);
}

/*
 * Vector math function
 * Multiply v1 with a scalar and store in result
 */
void rt_vectorMultiply(Vector *v1, double scalar, Vector *result)
{
    result->x = v1->x*scalar;
    result->y = v1->y*scalar;
    result->z = v1->z*scalar;
}

/*
 * Vector math function
 * Return dot product of v1 and v2 as double
 */
double rt_dotProduct(Vector *v1, Vector *v2)
{
    double v1x,v1y,v1z,
           v2x,v2y,v2z;
    double rx,ry,rz;

    v1x = v1->x; v1y = v1->y; v1z = v1->z;
    v2x = v2->x; v2y = v2->y; v2z = v2->z;

    rx = v1x*v2x; ry = v1y*v2y; rz = v1z*v2z;
    return rx + ry + rz; 
}

/*
 * Vector math function
 * Return length of the vector v
 * uses sqrt() from math.h
 */
double rt_vectorLength(Vector *v)
{
    double x,y,z;

    x = v->x; y = v->y; z = v->z;

    return sqrt((x*x) + (y*y) + (z*z));
}

/*
 * Vector math function
 * Returns normalized vector of vector v
 * in result. Uses rt_vectorLenght().
 */
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

/*
 * Determines surface normal for the object
 * based on point hit
 *
 * TODO: plane normal is not necessarily correct way
 * Maybe take this in account in intersection?
 */
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
        case t_plane:
        {
            Plane *p = (Plane *)object->object;
            normalHit->x = p->normal.x;
            normalHit->y = p->normal.y;
            normalHit->z = p->normal.z;
        } break;
        default:
            printf("[WARNING] Tried to calculate surface normal of unkown object type: %d\n",object->type);
        break;
    }
}

/*
 * Determine if intersection exists for the ray and
 * object. Returns 0 if no intersection or intersection
 * is behind the viewpoint. Returns scalar to multiply
 * ray direction vector to get to intersection point
 * otherwise.
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

            rt_vectorSubstract(&(s->position),&(ray->position),&distance);

            B = rt_dotProduct(&(ray->direction),&distance);
            
            /* Ray direction is not going towards origo */
            if(B < 0.0) return 0.0;
            
            D = rt_dotProduct(&distance,&distance) - B*B;
            radius2 = (s->radius)*(s->radius);

            /* No real roots, no intersection */
            if(D > radius2) return 0.0;
            D = sqrt(radius2-D);

            /* Smaller root first */
            t = B - D;
            if(t < 0.0) t = B + D;
            if(t < 0.0) return 0.0;

            /* t is not too close or behind the viewpoint */
            return t;

        } break;
        case t_plane:
        {
            Plane *p = (Plane *) object->object;
            Vector normal, position; double dotA,dotB, d; //ebin dota
            
            /* Dot product of plane normal and ray direction */
            dotA = rt_dotProduct(&(ray->direction),&(p->normal));

            /* Plane is perpendicular infinite or no intersections */
            if(0.0 == dotA)
                return 0.0;

            rt_vectorSubstract(&(p->position),&(ray->position),&(position));
            dotB = rt_dotProduct(&position,&(p->normal));
            
            d = dotB/dotA;

            /* Intersection is behind viewpoint */
            if(d < 0.0)
                return 0.0;
            
            return d;
        }    
        break;
        default:
            printf("[WARNING] Tried to calculate intersection for unkown object type: %d\n",object->type);
        break;
    }

    /* We do not know how to calculate intersection 
     * for unkown object
     */
    return 0.0;    
}

/*
 * Returns strength of light on the point depending
 * on angle between visible ligths and the point.
 * Value cannot exceed 1.0
 *
 * TODO: Not very realistic model, needs improvement.
 * Works only for point lights. Add support for illuminating
 * objects. Spherical lights?
 */
double rt_illumination(Vector *pointHit, Vector *normalHit)
{
    Ray shadowRay; int inShadow, i,j;
    double brightness, lightDistance, t;
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

        rt_vectorSubstract(&(light),&(shadowRay.position),&(shadowRay.direction));
        lightDistance =  rt_vectorLength(&(shadowRay.direction));
        rt_vectorNormalize(&(shadowRay.direction),&(shadowRay.direction));

        inShadow = 0;
        for(j=0;j<scene.objectCount;j++)
        {
            t = rt_intersect(&shadowRay,&(scene.objects[j])); 
            if(t > 0.0 && t < lightDistance)
                inShadow = 1;
        }

        if(0 == inShadow)
            brightness += rt_dotProduct(&shadowRay.direction,normalHit) * scene.lights[i].intensity;
    }
    if(brightness > 1.0) brightness = 1.0;
    return brightness;
}

/*
 * Trace a color for single ray
 * Color may be affected by other rays.
 * 
 * TODO: refraction support. fresnel equation
 */
Color rt_trace(Ray *ray, int recursions)
{
    Object *object; Color c;
    Vector pointHit, normalHit;
    double minDist, t; int i;

    object = NULL;
    minDist = INFINITY;
    c.r = 0; c.g = 0; c.b = 0;
    
    /* Find out closest intersection, if any */
    for(i=0;i<scene.objectCount;i++)
    {
        t = rt_intersect(ray,&(scene.objects[i]));
        if(t > 0.0 && t < minDist)
        {
            minDist = t;
            object = &scene.objects[i];
        }
    }

    /* If there was an intersection */
    if(NULL != object)
    {
        double brightness;

        /* Calculate point hit */
        rt_vectorMultiply(&(ray->direction),minDist,&pointHit);
        rt_vectorAdd(&pointHit,&(ray->position),&pointHit);

        /* Calculate normal hit */
        rt_surfaceNormal(object,&pointHit,&normalHit);

        /* Return light intensity on the intersection point
         * based on angles between visible light sources
         * Not very realistic.
         */
        brightness = rt_illumination(&pointHit,&normalHit);
        
        /* Object is reflective or transparent */
        if((object->reflection > 0 || object->transparency > 0) && (recursions > 0))
        {
            Color reflectionColor, refractionColor, diffuseColor;
            Ray reflectionRay, refractionRay; double reflet;

            if(object->reflection > 0)
            {
                reflectionRay.position.x = pointHit.x + normalHit.x * BIAS;
                reflectionRay.position.y = pointHit.y + normalHit.y * BIAS;
                reflectionRay.position.z = pointHit.z + normalHit.z * BIAS;

                reflet = rt_dotProduct(&(ray->direction),&normalHit); 
                reflet *= 2.0;
                rt_vectorMultiply(&normalHit,reflet,&(reflectionRay.direction));
                rt_vectorSubstract(&(ray->direction),&(reflectionRay.direction),&(reflectionRay.direction));

                reflectionColor = rt_trace(&reflectionRay, recursions-1);

            }
            if(object->transparency > 0)
            {
                //TODO
            }

            c.r = (int) (reflectionColor.r * (object->reflection)) + 0.5;
            c.g = (int) (reflectionColor.g * (object->reflection)) + 0.5;
            c.b = (int) (reflectionColor.b * (object->reflection)) + 0.5;
            
            if(brightness > 0)
            {
                diffuseColor.r = (int) ((1 - (object->reflection)) * (object->color.r * brightness) + 0.5);
                diffuseColor.g = (int) ((1 - (object->reflection)) * (object->color.g * brightness) + 0.5);
                diffuseColor.b = (int) ((1 - (object->reflection)) * (object->color.b * brightness) + 0.5);

                c.r += diffuseColor.r;
                c.g += diffuseColor.g;
                c.b += diffuseColor.b;
            }
        }
        /* Diffuse object */
        else
        {
            /* Calculate color */
            if(brightness > 0)
            {
                c.r = object->color.r;
                c.g = object->color.g;
                c.b = object->color.b;
                
                c.r = (int) c.r*brightness+0.5;
                c.g = (int) c.g*brightness+0.5;
                c.b = (int) c.b*brightness+0.5;
            }
        }
    }
    return c;
}

/* 
 * Trace color for each pixel and store resulting
 * color in an array
 *
 * TODO: Add fov calculation
 */
void rt_renderScene(Pixel *pixels)
{
    int x,y; Color c;
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
            c = rt_trace(&primaryRay,MAXRECURSION);
            pixels[y*scene.screenX+x] = gfx_createPixel(c.r,c.g,c.b);
            primaryRay.position.x += 1;
        }
        primaryRay.position.y += 1;
    }
}
