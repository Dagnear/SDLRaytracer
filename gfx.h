/* Storing the result in array of pixels */
typedef Uint32 Pixel; /* SDL rgb color format */

typedef struct
{
    int width;
    int height;
    Pixel *pixels;
} Bitmap;

void gfx_init(int width, int height, char *title);
void gfx_cleanup();
void gfx_putPixel(int x, int y, Uint32 color);
void gfx_update();
void gfx_lockBuffer();
void gfx_unlockBuffer();
Pixel gfx_getPixel(int r, int g, int b);
void gfx_fillBuffer(Pixel color);

/* Variables */
SDL_Surface *screen;
SDL_Surface *buffer;
