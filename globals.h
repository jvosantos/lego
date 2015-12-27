/*
 * globals.h
 * Declaration and initialization of global variables.
 *
 * badpointer - Nov/2011
 */

#ifndef _globals_h
#define _globals_h

/* "imports" */
/* ------------------------------------------------------------------ */
#include <GL/glut.h>
/* ------------------------------------------------------------------ */

/* global variables */
/* ------------------------------------------------------------------ */
/* viewing window vars */
double dim;	/* dimension of orthogonal box */ 

double zNear;
double zFar;
double right;
double left;
double bottom;
double top;

char* windowName;

int windowWidth;
int windowHeight;
int WINDOW_INITIAL_X;
int WINDOW_INITIAL_Y;

/* various global state */
int toggleGrid;
int toggleAxes; /* toggle axes on and off */
int toggleValues; /* toggle values on and off*/
int toggleMode; /* projection mode */
int th; /* azimuth of view angle */
int ph; /* elevation of view angle */
int fov; /* field of view for perspective */
int asp; /* aspect ratio */

/* ------------------------------------------------------------------ */

/* Auxiliar Types */
/* ------------------------------------------------------------------ */
/* pointers to surfaces data structures arrays*/
typedef GLfloat* point3D;
typedef GLfloat* vector3D;
typedef GLint* triangle;

/* Record to keep all info on a model */
typedef struct
{
	/* The Model */
	/* Number of entities */
	GLint numVertices;
	GLint numFaces;

	/* pointers to arrays */
	point3D* vertices;
	triangle* faces;
	vector3D* normals; /* normal vector to each face */

	/* properties */
	/* use a (sub-)record for material properties ?? */
	/* Arrays */
    GLfloat coefReflAmbiente[4];
    GLfloat coefReflDifusa[4];
    GLfloat coefReflEspecular[4];
    GLfloat coefDePhong[1];

	/* transformation parameters */
	float translX, translY, translZ;
	float rotAngXX, rotAngYY, rotAngZZ;
	float factorX, factorY, factorZ;

	/* Animation controls */
	int rotationOnXX, rotationOnYY, rotationOnZZ;
} Model_Record;

typedef Model_Record *modelPointer;

/* Record to save specs and global parameters of a spotlight transf. */
typedef struct
{
	int spotlightIsOn;

	unsigned int light;

	/* position in homogenic coords */
	GLfloat position[4];

	/* properties */
	/* Use a (sub-)record for spotlight properties ?? */
	/* Arrays */
	GLfloat compAmbiente[4];
	GLfloat compDifusa[4];
	GLfloat compEspecular[4];

	/* Add associated constants to the factor of atenuation */
	/* transformation parameters */
	float translX, translY, translZ;
	float rotAngXX, rotAngYY, rotAngZZ;

	/* Animation controls */
	int rotationOnXX, rotationOnYY, rotationOnZZ;
} Spotlight_Record;

typedef Spotlight_Record *spotlightPointer;

/* pointer for temporary model */
modelPointer tmpModel;

/* array of permanent models */
modelPointer * models;
int numberModels;

/* pointer to a spotlight */
spotlightPointer pSpotlight1;
spotlightPointer pSpotlight2;
spotlightPointer pSpotlight3;
spotlightPointer pSpotlight4;
spotlightPointer pSpotlight5;

int filledPositions[50][50][100];

/* ------------------------------------------------------------------ */

#endif
