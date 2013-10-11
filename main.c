/*
 * Minimalistic raytracer
 */
#include "includes.h"

void
cleanup()
{
    gfx_cleanup();
}

int
main(int argc, char **argv)
{
    printf("Hello raytracer\n");

    cleanup();

    return 0;
}
