/*
 * materialProps.c
 * MATERIALPROPS implementation file - contains the code to paint Legos
 * using plastic colors
 *
 * References : http://devernay.free.fr/cours/opengl/materials.html
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdlib.h>
#include "globals.h"
#include "materialProps.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void paintPlasticRed( modelPointer mod )
{
    mod->coefReflAmbiente[0] = 0.0;
    mod->coefReflAmbiente[1] = 0.0;
    mod->coefReflAmbiente[2] = 0.0;
    mod->coefReflAmbiente[3] = 1.0;
   
    mod->coefReflDifusa[0] = 0.5;
    mod->coefReflDifusa[1] = 0.0;
    mod->coefReflDifusa[2] = 0.0;
    mod->coefReflDifusa[3] = 1.0;

    mod->coefReflEspecular[0] = 0.7;
    mod->coefReflEspecular[1] = 0.6;
    mod->coefReflEspecular[2] = 0.6;
    mod->coefReflEspecular[3] = 1.0;
   
    mod->coefDePhong[0] = 32.0;
}

void paintPlasticYellow( modelPointer mod )
{
    mod->coefReflAmbiente[0] = 0.0;
    mod->coefReflAmbiente[1] = 0.0;
    mod->coefReflAmbiente[2] = 0.0;
    mod->coefReflAmbiente[3] = 1.0;
   
    mod->coefReflDifusa[0] = 0.5;
    mod->coefReflDifusa[1] = 0.5;
    mod->coefReflDifusa[2] = 0.0;
    mod->coefReflDifusa[3] = 1.0;

    mod->coefReflEspecular[0] = 0.6;
    mod->coefReflEspecular[1] = 0.6;
    mod->coefReflEspecular[2] = 0.5;
    mod->coefReflEspecular[3] = 1.0;
   
    mod->coefDePhong[0] = 32.0;
}

void paintPlasticWhite( modelPointer mod )
{
    mod->coefReflAmbiente[0] = 0.0;
    mod->coefReflAmbiente[1] = 0.0;
    mod->coefReflAmbiente[2] = 0.0;
    mod->coefReflAmbiente[3] = 1.0;
   
    mod->coefReflDifusa[0] = 0.55;
    mod->coefReflDifusa[1] = 0.55;
    mod->coefReflDifusa[2] = 0.55;
    mod->coefReflDifusa[3] = 1.0;

    mod->coefReflEspecular[0] = 0.7;
    mod->coefReflEspecular[1] = 0.7;
    mod->coefReflEspecular[2] = 0.7;
    mod->coefReflEspecular[3] = 1.0;
   
    mod->coefDePhong[0] = 32.0;
}

void paintPlasticGreen( modelPointer mod )
{
    mod->coefReflAmbiente[0] = 0.0;
    mod->coefReflAmbiente[1] = 0.0;
    mod->coefReflAmbiente[2] = 0.0;
    mod->coefReflAmbiente[3] = 1.0;
   
    mod->coefReflDifusa[0] = 0.1;
    mod->coefReflDifusa[1] = 0.35;
    mod->coefReflDifusa[2] = 0.1;
    mod->coefReflDifusa[3] = 1.0;

    mod->coefReflEspecular[0] = 0.45;
    mod->coefReflEspecular[1] = 0.55;
    mod->coefReflEspecular[2] = 0.45;
    mod->coefReflEspecular[3] = 1.0;
   
    mod->coefDePhong[0] = 32.0;
}

void paintPlasticCyan( modelPointer mod )
{
    mod->coefReflAmbiente[0] = 0.0;
    mod->coefReflAmbiente[1] = 0.1;
    mod->coefReflAmbiente[2] = 0.06;
    mod->coefReflAmbiente[3] = 1.0;
   
    mod->coefReflDifusa[0] = 0.0;
    mod->coefReflDifusa[1] = 0.50980392;
    mod->coefReflDifusa[2] = 0.50980392;
    mod->coefReflDifusa[3] = 1.0;

    mod->coefReflEspecular[0] = 0.50196078;
    mod->coefReflEspecular[1] = 0.50196078;
    mod->coefReflEspecular[2] = 0.50196078;
    mod->coefReflEspecular[3] = 1.0;
   
    mod->coefDePhong[0] = 32.0;
}
/* ------------------------------------------------------------------ */