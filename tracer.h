/* Structures */
typedef struct
{
    float x;
    float y;
    float z;
} Vector;

/* Ray of 'light' */
typedef struct
{
    Vector position;
    Vector direction;
} Ray;

typedef struct
{
    Vector position;
    float intensity;
} Light;

/* Enumertions for different entity types
 * maybe extend beyond spheres in the future?
 */
enum t_object
{
    t_null, //No object assigned
    t_sphere,
    t_plane
};

typedef struct
{
    enum t_object type;
    void *object;
} Object;

typedef struct
{
    Vector position;
    float radius;
} Sphere;

/* Components of a scene */
typedef struct
{
    int screenX;
    int screenY;

    Vector cameraPosition;
    Vector cameraDirection;

    int lightCount;
    Light *lights;

    int objectCount;
    Object *objects;

} Scene;

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

void rt_vectorSubstract(Vector *v1, Vector *v2, Vector *result);
void rt_vectorAdd(Vector *v1, Vector *v2, Vector *result);
void rt_vectorMultiply(Vector *v1, float scalar, Vector *result);
void rt_dotProduct(Vector *v1, Vector *v2, Vector *result);
