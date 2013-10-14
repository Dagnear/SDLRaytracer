/* Enumertions for different entity types
 * maybe extend beyond spheres in the future?
 */
enum entity_type
{
    t_sphere
    t_plane;
};

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

/* Is this a bit redundant? */
typedef struct
{
    Vector position;
    Vector direction;
} Camera;

typedef struct
{
    Vector position;
    int radius;
} Sphere;

/* Possibility for different shapes */
typedef struct
{
    int type;
    void *entity;
} Entity;

/* Components of a scene */
typedef struct
{
    Camera camera;

    int lightCount;
    Vector *lights;

    int entityCount;
    Entity *entities;

} Scene;

