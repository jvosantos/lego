/*
 * models.h
 * MODELS header file
 *
 * badpointer - Nov/2011
 */

#ifndef _models_h
#define _models_h

#include "globals.h"

/* public methods */
/* ------------------------------------------------------------------ */

/* Creates and returns a lego model with given dimensions
=======================================================================
		length -> number os units in the xx'
		width -> number os units in the zz'
		heigth -> fixed at 1
	Each unit size is "1.0 x 1.0 x 1.0" 
		("1.0 x 1.2 x 1.0" if we count the cylinder on top) 
	The model is built starting at "0.0 x 0.0 x 0.0" and grows to positive sides 
		(lego is centered at "length/2 x 0.5 x width/2" not counting the cylinders)
======================================================================*/
modelPointer createLego( int length, int width );

void drawShape( void );

void drawAxes( void );

void drawGrid( void );
/* ------------------------------------------------------------------ */

#endif
