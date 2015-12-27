/*
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdlib.h>
#include "globals.h" 
#include "spotlights.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
spotlightPointer createSpotlight( void )
{
	static unsigned int lights[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
	static int nLight = 0;

	spotlightPointer pSpotlight = ( Spotlight_Record* ) malloc( sizeof( Spotlight_Record ) );

	pSpotlight->spotlightIsOn = 1;

	pSpotlight->light = lights[nLight++];

	pSpotlight->compAmbiente[0] = 1.0;
	pSpotlight->compAmbiente[1] = 1.0;
	pSpotlight->compAmbiente[2] = 1.0;
	pSpotlight->compAmbiente[3] = 1.0;

	pSpotlight->compDifusa[0] = 1.0;
	pSpotlight->compDifusa[1] = 1.0;
	pSpotlight->compDifusa[2] = 1.0;
	pSpotlight->compDifusa[3] = 1.0;

	pSpotlight->compEspecular[0] = 1.0;
	pSpotlight->compEspecular[1] = 1.0;
	pSpotlight->compEspecular[2] = 1.0;
	pSpotlight->compEspecular[3] = 1.0;

	pSpotlight->position[0] = 0.0;
	pSpotlight->position[1] = 0.0;
	pSpotlight->position[2] = 0.0;
	pSpotlight->position[3] = 1.0;

	pSpotlight->translX = 0.0;
	pSpotlight->translY = 0.0;
	pSpotlight->translZ = 0.0;

	pSpotlight->rotAngXX = 0;
	pSpotlight->rotAngYY = 0;
	pSpotlight->rotAngZZ = 0;

	pSpotlight->rotationOnXX = 0;
	pSpotlight->rotationOnYY = 0;
	pSpotlight->rotationOnZZ = 0;

	return pSpotlight;
}

/* ------------------------------------------------------------------ */
