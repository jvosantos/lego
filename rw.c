/*
 * rw.c
 * RW implementation file - contains the code used to read and write
 * models to and from files 
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "dataStructs.h"
#include "consoleIO.h"
#include "globals.h" 
/* ------------------------------------------------------------------ */

/* private methods */
/* ------------------------------------------------------------------ */
int writeModel( modelPointer tmpMod, FILE *outputFileStream)
{
	int i,j;

	if( fprintf(outputFileStream, "%d\n", tmpMod->numVertices) < 0)	return -1;
	if( fprintf(outputFileStream, "%d\n", tmpMod->numFaces) < 0)	return -1;
	/* all vertexes */	
	for(i=0; i<tmpMod->numVertices; i++)
	{
		if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->vertices[i][0], tmpMod->vertices[i][1], tmpMod->vertices[i][2]) < 0)	return -1;
	}
	/* all triangles */
	for(i=0; i<tmpMod->numFaces; i++)
	{
		if( fprintf(outputFileStream, "%d %d %d\n", tmpMod->faces[i][0], tmpMod->faces[i][1], tmpMod->faces[i][2]) < 0)	return -1;
	}

	/* all normal vectors */
	for(i=0; i<tmpMod->numFaces; i++)
	{
		//if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->normals[i][0], tmpMod->normals[i][1], tmpMod->normals[i][2]) < 0) return -1;
		for(j=0; j<3; j++)
			if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][0], tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][1], tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][2]) < 0) return -1;	
	}

	/* ligthing coefficients */
	if( fprintf(outputFileStream, "%f %f %f %f\n", tmpMod->coefReflAmbiente[0], tmpMod->coefReflAmbiente[1], tmpMod->coefReflAmbiente[2], tmpMod->coefReflAmbiente[3]) < 0)	return -1;	

	if( fprintf(outputFileStream, "%f %f %f %f\n", tmpMod->coefReflDifusa[0], tmpMod->coefReflDifusa[1], tmpMod->coefReflDifusa[2], tmpMod->coefReflDifusa[3]) < 0)	return -1;	

	if( fprintf(outputFileStream, "%f %f %f %f\n", tmpMod->coefReflEspecular[0], tmpMod->coefReflEspecular[1], tmpMod->coefReflEspecular[2], tmpMod->coefReflEspecular[3]) < 0)	return -1;	

	if( fprintf(outputFileStream, "%f\n", tmpMod->coefDePhong[0]) < 0)	return -1;	

	/* translations, rotations, scalings and animations */
	if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->translX, tmpMod->translY, tmpMod->translZ) < 0)	return -1;

	if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->rotAngXX, tmpMod->rotAngYY, tmpMod->rotAngZZ) < 0)	return -1;

	if( fprintf(outputFileStream, "%f %f %f\n", tmpMod->factorX, tmpMod->factorY, tmpMod->factorZ) < 0)	return -1;

	if( fprintf(outputFileStream, "%d %d %d\n", tmpMod->rotationOnXX, tmpMod->rotationOnYY, tmpMod->rotationOnZZ) < 0)	return -1;
		
	return 0;
}

int readModel( int modelIndex, FILE *inputFileStream )
{
	int i, j;
	modelPointer tmpMod = (Model_Record*) malloc(sizeof(Model_Record));

	if( fscanf(inputFileStream, "%d\n", &tmpMod->numVertices) < 0)	return -1;
	if( fscanf(inputFileStream, "%d\n", &tmpMod->numFaces) < 0)	return -1;

	tmpMod->vertices = (GLfloat**) calloc(tmpMod->numVertices, sizeof(GLfloat*));
	/* all vertexes */	
	for(i=0; i<tmpMod->numVertices; i++)
	{
		tmpMod->vertices[i] = (GLfloat*) calloc(3, sizeof(GLfloat));
		if( fscanf(inputFileStream, "%f %f %f\n", &tmpMod->vertices[i][0], &tmpMod->vertices[i][1], &tmpMod->vertices[i][2]) < 0)	return -1;
	}

	tmpMod->faces = (GLint**) calloc(tmpMod->numFaces, sizeof(GLint*));
	/* all triangles */
	for(i=0; i<tmpMod->numFaces; i++)
	{
		tmpMod->faces[i] = (GLint*) calloc(3, sizeof(GLint));
		if( fscanf(inputFileStream, "%d %d %d\n", &tmpMod->faces[i][0], &tmpMod->faces[i][1], &tmpMod->faces[i][2]) < 0)	return -1;
	}

	tmpMod->normals = (GLfloat**) calloc(tmpMod->numFaces*3, sizeof(GLfloat*));
	/* all normal vectors */
	for(i=0; i<tmpMod->numFaces; i++)
	{
		for(j=0; j<3; j++)
		{
			tmpMod->normals[indexTriangleVertex(j, i, tmpMod)] = (GLfloat*) calloc(3, sizeof(GLfloat));
			if( fscanf(inputFileStream, "%f %f %f\n", &tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][0], &tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][1], &tmpMod->normals[indexTriangleVertex(j, i, tmpMod)][2]) < 0) return -1;
		}
	}

	/* ligthing coefficients */
	if( fscanf(inputFileStream, "%f %f %f %f\n", &tmpMod->coefReflAmbiente[0], &tmpMod->coefReflAmbiente[1], &tmpMod->coefReflAmbiente[2], &tmpMod->coefReflAmbiente[3]) < 0)	return -1;	

	if( fscanf(inputFileStream, "%f %f %f %f\n", &tmpMod->coefReflDifusa[0], &tmpMod->coefReflDifusa[1], &tmpMod->coefReflDifusa[2], &tmpMod->coefReflDifusa[3]) < 0)	return -1;	

	if( fscanf(inputFileStream, "%f %f %f %f\n", &tmpMod->coefReflEspecular[0], &tmpMod->coefReflEspecular[1], &tmpMod->coefReflEspecular[2], &tmpMod->coefReflEspecular[3]) < 0)	return -1;	

	if( fscanf(inputFileStream, "%f\n", &tmpMod->coefDePhong[0]) < 0)	return -1;	

	/* translations, rotations, scalings and animations */
	if( fscanf(inputFileStream, "%f %f %f\n", &tmpMod->translX, &tmpMod->translY, &tmpMod->translZ) < 0)	return -1;

	if( fscanf(inputFileStream, "%f %f %f\n", &tmpMod->rotAngXX, &tmpMod->rotAngYY, &tmpMod->rotAngZZ) < 0)	return -1;

	if( fscanf(inputFileStream, "%f %f %f\n", &tmpMod->factorX, &tmpMod->factorY, &tmpMod->factorZ) < 0)	return -1;

	if( fscanf(inputFileStream, "%d %d %d\n", &tmpMod->rotationOnXX, &tmpMod->rotationOnYY, &tmpMod->rotationOnZZ) < 0)	return -1;
		
	models[modelIndex] = tmpMod;
	return 0;
}
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
int writeConstruction( void )
{
	FILE *outputFileStream;
	char * fileName = "construction.lgo";
	int i;

	/* open file for writing */
	if((outputFileStream = fopen(fileName, "w")) == NULL)
	{
		debug("**********ERROR**********\n\tError while opening file for writing.\n**********/ERROR*********\n");
		return -1;
	} 

	/* write number of models into the file */
	if( fprintf(outputFileStream, "%d\n", numberModels) < 0 )
	{
		debug("**********ERROR**********\n\tError while writing number of models in construction to the file.\n**********/ERROR*********\n");
		return -2;
	}

	/* write all moedls into the file */
	for(i = 0; i<numberModels; i++)
	{
		if( writeModel(models[i], outputFileStream) < 0 )
		{
			debug("**********ERROR**********\n\tError while writing model to the file.\n**********/ERROR*********\n");
			return -3;
		}
	}
	
	debug("Construction written with sucess\n");
	
	/* close fileStream */
	fclose(outputFileStream);

	return 0;
}

int readConstruction( void )
{
	FILE *inputFileStream;
	char * fileName = "construction.lgo";
	int i;

	/* open file for reading */
	if((inputFileStream = fopen("construction.lgo", "r")) == NULL)
	{
		debug("**********ERROR**********\n\tError while opening file for reading. Does the file exists?\n**********/ERROR*********\n");
		return -1;
	} 

	/* read number of models on the file */
	if( fscanf(inputFileStream, "%d", &numberModels) < 0)
	{
		debug("**********ERROR**********\n\tError while reading number of models in construction to the file.\n**********/ERROR*********\n");
		return -2;
	}

	/* read all models from the file */
	for(i=0; i<numberModels; i++)
	{
		if( readModel(i, inputFileStream) < 0 )
		{
			debug("**********ERROR**********\n\tError while reading model from the file.\n**********/ERROR*********\n");
			return -3;
		}
	}

	debug("Construction has been read with sucess\n");
	
	/* close fileStream */
	fclose(inputFileStream);

	return 0;
}
/* ------------------------------------------------------------------ */
