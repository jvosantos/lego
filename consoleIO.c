/*
 * consoleIO.h
 * CONSOLEIO implementation file -contains the code used to communicate 
 * with the console, either being input or output functions.
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include "consoleIO.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void howToInfo( void )
{
	printf("\n###########\n# HOW TO: #\n###########\n");
	printf("\tTo quit the programn simply press \"ESC\"\n");
	printf("\tTo switch between perspective mode and ortogonal mode, press \"m\"\n");
	printf("\tTo move around the grid, press the arrows keys (up, down, left, right)\n");
	printf("\tTo zoom in and zoom out press \"d\", \"D\", \"+\", \"-\" depending if you are in perspective or orthogonal mode\n");
	printf("\tTo move a lego piece around on all axis\n\t\tpress \"j\", \"l\" for the XX axis\n\t\tpress \"i\", \"k\" for the YY axis\n\t\tpress \"u\", \"o\" for the ZZ axis\n");
	printf("\tTo turn on or off the grid press \"g\"\n");
	printf("\tTo know where the origin is press \"a\"\n");
	printf("\tTo paint a temporary piece choose a colour use one of the following keys: \"1\", \"2\", \"3\", \"4\", \"5\"\n"); 
	printf("\tTo turn a temporary piece into a permanent piece of the construction press \"ENTER\"\n");
	printf("\tfor other options, use the right mouse menu button\n");
}

void debug( char * s )
{
	printf("\n** DEBUG ** : %s\n", s);
}

/* ------------------------------------------------------------------ */
