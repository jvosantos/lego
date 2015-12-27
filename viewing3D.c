/*
 * viewing3D.c
 * VIEWING3D implementation file - contains the code for stuff 
 * regarding 3D stuff.
 * INIT implementation file - contains the code used to initialize 
 * stuff.
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <GL/glut.h>
#include "viewing3D.h"
#include "globals.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void project( void )
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(toggleMode){
		//gluPerspective(fov, asp, dim/4, 4*dim);
		gluPerspective(fov, asp, zNear, zFar);
	}
	else{
		//glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
		glOrtho(left, right, bottom, top, zNear, zFar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void transfWindowViewport( void )
{
	float aspectRatio;
	float middleX, middleY;
	float newWindowHeightXOY, newWindowWidthXOY;

	/* Do nothing if the window has been minimized */
	if( (windowHeight < 1) || (windowWidth<1) )
		return;
	
	/* establish the window*/
	/* use window dimentions to determin aspect ratio */
	/* occupie biggest possible area without distortions */
	if( windowWidth <= windowHeight )
	{
		/* adjust window height on XOY plane */
		/* aspect ratio of output window */
		aspectRatio = (float) windowHeight / (float) windowWidth;

		/* for the window on XOY plane */
		middleY = (float) ( bottom + top ) / 2.0;
		newWindowHeightXOY = aspectRatio * ( right - left );

		/* keep the center of window on the plane */
		bottom = middleY - newWindowHeightXOY / 2;
		top = middleY + newWindowHeightXOY / 2;
	}
	else
	{
		/* adjust window height on XOY plane */
		/* aspect ratio of output window */
		aspectRatio = (float) windowWidth / (float) windowHeight;

		/* for the window on XOY plane */
		middleX = (float) ( left + right ) / 2.0;
		newWindowWidthXOY = aspectRatio * ( top - bottom );

		/* keep the center of window on the plane */
		left = middleX - newWindowWidthXOY / 2;
		right = middleX + newWindowWidthXOY / 2;
	}

	/* establish visual volume */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	asp = aspectRatio;
	
	/*Use all output window */
	glViewport( 0, 0, windowWidth, windowHeight);

	project();
}

/* ------------------------------------------------------------------ */
