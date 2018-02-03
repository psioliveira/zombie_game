
#include <stdio.h>
#include <stdlib.h>
#include "showworld.h"
#include "functions.h"

/* The implementation of `SHOWWORLD` type used in this simple text-based world
 * visualization code. In this simple case, we only need to keep track of the
 * world dimensions and of the function pointer which knows how to read an
 * agent from the world data structure.
 *
 * For a more complex implementation, for example based on the g2 library,
 * it would also be necessary to keep the g2 device.
 * */
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};

/* Create a new display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_new()` prototype defined in
 * `showworld.h`. */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func) {

    SHOWWORLD *sw = NULL;
    sw = malloc(sizeof(SHOWWORLD));
    sw->xdim = xdim;
    sw->ydim = ydim;
    sw->aginfo_func = aginfo_func;
    return sw;

}

/* Destroy a display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_destroy()` prototype defined in
 * `showworld.h`. */
void showworld_destroy(SHOWWORLD *sw) {
    free(sw);
}

/* Update the simulation world display/visualization.
 *
 * This function obeys the `showworld_update()` prototype defined in
 * `showworld.h`. */
void showworld_update(SHOWWORLD *sw, WORLD *w) {

    printf("\n");

    /* Cycle through all the rows */
    for (unsigned int y = 0; y < sw->ydim; ++y) {

        /* Cycle through all the columns for the current row */
        for (unsigned int x = 0; x < sw->xdim; ++x) {

            /* Get state of the world (in bit packed fashion) using the user
               supplied function. */
            unsigned int item = sw->aginfo_func(w, x, y);

            /* Extract the agent type (2 bits). */
            AGENT_TYPE ag_type = item & 0x3;
            /* Extract whether the agent is playable (1 bit). */
            unsigned char playable = (item >> 2) & 0x1;
            /* Extract the agent ID (16 bits). */
            unsigned short ag_id = (item >> 3) & 0xFFFF;

            /* Determine the agent type. */
            switch (ag_type) {

                /* If no agent is present at (x,y) just print a dot. */
                case None:
                    printf(" .  ");
                    break;

                /* If human agent present at (x,y) print 'h' or 'H'. */
                case Human:
                    if (playable) {
                        /* Uppercase 'H' for player-controlled human agent. */
                        printf("H");
                    } else if (!playable) {
                        /* Lowercase 'h' for AI-controlled human agent. */
                        printf("h");
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* If zombie agent present at (x,y) print 'z' or 'Z'. */
                case Zombie:
                    if (playable) {
                        /* Uppercase 'Z' for player-controlled zombie agent. */
                        printf("Z");
                    } else {
                        /* Lowercase 'z' for AI-controlled zombie agent. */
                        printf("z");
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* Print '?' if unknown type detected. This should *never*
                   happen. */
                default:
                    printf("?   ");

            }
        }

        /* Print two newlines after each row. */
        printf("\n\n");

    }

    /* Print a newline after world is shown/updated. */
    printf("\n");

}

