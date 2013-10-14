/* Structures */
typedef struct
{
    int x;
    int y;
    int z;
} Vector;

/* Ray of 'light' */
typedef struct
{
    Vector position;
    Vector direction;
} Ray;

/* Enumertions for different entity types
 * maybe extend beyond spheres in the future?
 */
enum t_object
{
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
    unsigned radius;
} Sphere;

/* Components of a scene */
typedef struct
{
    Vector cameraPosition;
    Vector cameraDirection;

    int lightCount;
    Vector *lights;

    int objectCount;
    Object *objects;

} Scene;

