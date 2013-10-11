/* Storing the result in array of pixels */
typedef Uint32 Pixel; /* SDL rgb color format */

typedef struct
{
    int width;
    int height;
    Pixel *pixels;
}; Bitmap;
