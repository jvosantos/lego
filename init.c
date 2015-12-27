/*
 * init.h
 * INIT implementation file - contains the code used to initialize 
 * stuff.
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "init.h"
#include "viewing3D.h"
#include "globals.h"
#include "spotlights.h"
#include "models.h"
#include "materialProps.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void initVariables( void )
{
	dim=6.0;

	top = 6.0;
	bottom = -6.0;
	left = -6.0;
	right = 6.0;
	zNear = 12.0;
	zFar = -12.0;

	windowWidth=800;
	windowHeight=800;
	WINDOW_INITIAL_X = 100;
	WINDOW_INITIAL_Y = 100;

	toggleAxes = 0;
	toggleValues = 1;
	toggleMode = 0;
	toggleGrid = 1;
	th = 15;
	ph = -15;
	fov = 55;
	asp = 1;

	models = (modelPointer*) calloc(100, sizeof(Model_Record));
	numberModels = 0;

	tmpModel = NULL;
	tmpModel = createLego(1,1);
	
	paintPlasticRed(tmpModel);
}

void initWindow( void )
{
   /* Double-buffering + Depth-buffer */ 
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   
   /* Outter window definitions */
   /* Must initialize global associated variables */
   glutInitWindowSize( windowWidth, windowHeight ); 
   glutInitWindowPosition( WINDOW_INITIAL_X, WINDOW_INITIAL_Y );
   glutCreateWindow("Brincar com legos é fixe.");
}

void initSpotlights( void )
{
	glEnable(GL_LIGHTING);
	pSpotlight1 = createSpotlight();
	pSpotlight1->spotlightIsOn = 1;
	pSpotlight1->position[0] = -25.0;
	pSpotlight1->position[1] = 10.0;
	pSpotlight1->position[2] = 25.0;

	pSpotlight2 = createSpotlight();
	pSpotlight2->spotlightIsOn = 1;
	pSpotlight2->position[0] = -25.0;
	pSpotlight2->position[1] = 10.0;
	pSpotlight2->position[2] = -25.0;

	pSpotlight3 = createSpotlight();
	pSpotlight3->spotlightIsOn = 1;
	pSpotlight3->position[0] = 25.0;
	pSpotlight3->position[1] = 10.0;
	pSpotlight3->position[2] = -25.0;

	pSpotlight4 = createSpotlight();
	pSpotlight4->spotlightIsOn = 1;
	pSpotlight4->position[0] = 25.0;
	pSpotlight4->position[1] = 10.0;
	pSpotlight4->position[2] = 25.0;

	pSpotlight5 = createSpotlight();
	pSpotlight5->spotlightIsOn = 0;
	pSpotlight5->position[0] = 0.0;
	pSpotlight5->position[1] = 10.0;
	pSpotlight5->position[2] = 0.0;
}

/* ------------------------------------------------------------------ */
