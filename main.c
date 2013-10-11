/*
 * Minimalistic raytracer
 */
#include "includes.h"
#include "declare.h"

void
cleanup()
{
    gfx_cleanup();
}

int
main(int argc, char **argv)
{
    int run;

    printf("Hello raytracer\n");

    gfx_init("Hello raytracer!");
    atexit(cleanup);

    run = 1;
    while(1 == run)
    {
        getInput();
        SDL_Delay(16);
    }

    cleanup();

    return 0;
}
