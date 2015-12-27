/*
 * dataStructures.h
 * DATASTRUCTURES header file
 *
 * badpointer - Nov/2011
 */

#ifndef _dataStructures_h
#define _dataStructures_h

/* "imports" */
/* ------------------------------------------------------------------ */
#include <GL/glut.h>
#include "globals.h"
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */

point3D createVertex( GLfloat x, GLfloat y, GLfloat z );

point3D cloneVertex( point3D vert );

void imprimeVertice( point3D vert );

point3D createMiddlePoint( point3D p1, point3D p2 );

vector3D createVector( GLfloat x, GLfloat y, GLfloat z );

vector3D cloneVector( vector3D vect );

void imprimeVector( vector3D vect );

void converterParaVersor( vector3D v );

vector3D sumOfVectors( vector3D a, vector3D b );

triangle createTriangle( GLint ind1, GLint ind2, GLint ind3 );

GLint indexTriangleVertex( GLint i, GLint q, modelPointer p );

vector3D triangleNormal( point3D p1, point3D p2, point3D p3 );

/* ------------------------------------------------------------------ */

#endif
