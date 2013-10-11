/* Enumertions for different entity types
 * maybe extend beyond spheres in the future?
 */
enum entity_type
{
    Sphere
};

/* Structures */
typedef struct
{
    int x;
    int y;
    int z;
}; Vector;

typedef struct
{
    Vector position;
    Vector direction;
}; Ray;

typedef struct /* Is this a bit redundant? */
{
    Vector position;
    Vector direction;
}; Camera

typedef struct
{
    Vector position;
    int radius;
}; Sphere;

typedef struct
{
    int type;
    void *entity;
}; Entity;

/* Storing the result in array of pixels */
typedef struct
{
    Uint32 color;
}; Pixel

typedef struct
{
    int w;
    int h;
    Pixel *pixels;
}; Bitmap;
