/* Variables */
SDL_Surface *screen;

/* Enumertions */
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


