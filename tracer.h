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

