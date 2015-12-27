/*
 * models.h
 * MODELS implementation file - contains the code to create Lego models
 *
 * NOTE : Models are defined by triangular faces
 *        With one normal vector for each vertex
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataStructs.h"
#include "globals.h"
#include "models.h"
const double CONST_PI = 3.14159265358979323846;
/* ------------------------------------------------------------------ */

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
modelPointer createLego( int length, int width )
{
   /* Each triangular face has its own vertexes
      and the correct versors associated with each vertex */
   
   int c, i, j, k, nUnits;
   int facesBaixo, facesLat_porUnidade, facesTopo_porUnidade, facesLatCilindro_porUnidade, facesTopoCilindro_porUnidade;
   int iVertex, iFace;

   GLfloat xVert, zVert, xStep, zStep, xAng1, xAng2, zAng1, zAng2;
   GLfloat xCentroBase, yCentroBase, zCentroBase, xCentroCilindro, yCentroCilindro, zCentroCilindro;

   vector3D temp;
   
   /* Ponteiro para o registo do modelo criado */
   
   modelPointer pModelo = ( Model_Record* ) malloc( sizeof( Model_Record ) );
        
   /* Calcular Número de "unidades" de um lego (número de encaixes) */ 

   nUnits = length * width;

   facesBaixo = (length + width) * 2 * 4; // número de faces de baixo do lego

   facesLat_porUnidade = 8; // número de faces laterais por cada unidade 

   facesTopo_porUnidade = 16 * 2; // número de faces de cima por cada unidade (sem contar com o encaixe)

   facesLatCilindro_porUnidade = 16 * 2; // número de faces de cada cilindro/encaixe por cada unidade

   facesTopoCilindro_porUnidade = 16; // número de faces de cima de cada cilindro/encaixe por cada unidade

   iFace = iVertex = 0;

   /* Vertices e Faces Triangulares */
   
   /* (faces laterais e de baixo "(length+width) * 3 para nº faces unitárias (2) + faces de baixo (1), * 8 pk cada face unitári é dividiva em 8 triangulos)
       + (faces de cima) */

   pModelo->numFaces = ( (length + width) * 3 * 8 ) + ( nUnits * (5 * 16) );

   /* Vertices declarados explicitamente para cada face */

   pModelo->numVertices = pModelo->numFaces * 3;

   /* Espaco para os arrays */

   pModelo->vertices = (point3D*) calloc( pModelo->numVertices, sizeof( point3D ) );
        
   pModelo->faces = (triangle*) calloc( pModelo->numFaces, sizeof( triangle ) );
        
   pModelo->normals = (vector3D*) calloc( pModelo->numVertices, sizeof( vector3D ) );
   
   
   /* triangulos das faces da frente (CCW) */
   
	xVert = 0.0;
	xStep = 0.25;
	zVert = 1.0 * width;

	/* para cada unidade */
	for (i = 0; i < length; i++) 
	{
		/* cria duas faces de cada vez (os 2 triangulos de cada rectangulo que pertence uma face de cada unidade) */
		for (j = 0; j < facesLat_porUnidade/2; j++) 
		{
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			xVert += xStep;
		}
	}


	/* triangulos das faces da direita (CCW) */
   
	xVert = 1.0 * length;
	zVert = 1.0 * width;
	zStep = 0.25;

	/* para cada unidade */
	for (i = 0; i < width; i++) 
	{
		/* cria duas faces de cada vez (os 2 triangulos de cada rectangulo que pertence uma face de cada unidade) */
		for (j = 0; j < facesLat_porUnidade/2; j++) 
		{
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert - zStep );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert - zStep );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert - zStep );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			zVert -= zStep;
		}
	}


	/* triangulos das faces da rectaguarda (CW) */
   
	xVert = 1.0 * length;
	xStep = 0.25;
	zVert = 0.0;

	/* para cada unidade */
	for (i = 0; i < length; i++) 
	{
		/* cria duas faces de cada vez (os 2 triangulos de cada rectangulo que pertence uma face de cada unidade) */
		for (j = 0; j < facesLat_porUnidade/2; j++) 
		{
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 1.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			xVert -= xStep;
		}
	}


	/* triangulos das faces da esquerda (CW) */
   
	xVert = 0.0;
	zVert = 0.0;
	zStep = 0.25;

	/* para cada unidade */
	for (i = 0; i < width; i++) 
	{
		/* cria duas faces de cada vez (os 2 triangulos de cada rectangulo que pertence uma face de cada unidade) */
		for (j = 0; j < facesLat_porUnidade/2; j++) 
		{
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert + zStep );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert + zStep );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert + zStep );
			pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
			pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

			zVert += zStep;
		}
	}


	/* triangulos das faces da base (CW) */

	xCentroBase = length / 2.0;
    yCentroBase = 0.0;
	zCentroBase = width / 2.0;
	xStep = zStep = 0.25;

	xVert = 0.0;
	zVert = 1.0 * width;
	for (i = 0; i < length * 4; i++) // frente
	{
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
		pModelo->vertices[iVertex++] = createVertex( xCentroBase, 0.0, zCentroBase );
		pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 0.0, zVert );
		pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );
		xVert += xStep;
	}
	xVert = 1.0 * length;
	zVert = 1.0 * width;
	for (i = 0; i < width * 4; i++) // direita
	{
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
		pModelo->vertices[iVertex++] = createVertex( xCentroBase, 0.0, zCentroBase );
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert - zStep );
		pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );
		zVert -= zStep;
	}
	xVert = 1.0 * length;
	zVert = 0.0;
	for (i = 0; i < length * 4; i++) // rectaguarda
	{
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
		pModelo->vertices[iVertex++] = createVertex( xCentroBase, 0.0, zCentroBase );
		pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 0.0, zVert );
		pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );
		xVert -= xStep;
	}
	xVert = 0.0;
	zVert = 0.0;
	for (i = 0; i < width * 4; i++) // esquerda
	{
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert );
		pModelo->vertices[iVertex++] = createVertex( xCentroBase, 0.0, zCentroBase );
		pModelo->vertices[iVertex++] = createVertex( xVert, 0.0, zVert + zStep );
		pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );
		zVert += zStep;
	}


	/* triangulos das faces do Topo (CCW) */

	xCentroCilindro = 0.5;
	yCentroCilindro = 1.2;
	zCentroCilindro = 0.5;
	   
	xVert = 0.5;
	xStep = 0.25;
	zVert = 1.0;
	zStep = 0.25;

	for (i = 0; i < length; i++) 
	{
		for (j = 0; j < width ; j++)
		{
			xVert = 0.5 + i;
			zVert = 1.0 + j;
			for (k = 0; k < 2 ; k++) // baixo esquerda
			{
				zAng1 = 0.3 * cos( k * CONST_PI/8 ) + zCentroCilindro;
				xAng1 = 0.3 * sin( k * CONST_PI/8 ) + xCentroCilindro;
				zAng2 = 0.3 * cos( (k+1) * CONST_PI/8 ) + zCentroCilindro;
				xAng2 = 0.3 * sin( (k+1) * CONST_PI/8 ) + xCentroCilindro;

				/* Topo de uma unidade */
				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Faces laterais do cilindro CCW */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Cada vertice da face lateral do cilindro tem um versor normal : Met. de GOURAUD */
				/* Esse versor resulta de normalizar o vector posicao de cada vertice */
				for (c = 1; c <= 6; c++) {
					pModelo->normals[iVertex-c] = cloneVector( pModelo->vertices[iVertex-c] );
					converterParaVersor( pModelo->normals[iVertex-c] );
				}

				/* Topo do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xCentroCilindro, 1.2, zCentroCilindro );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				xVert += xStep;
			}
			xVert = 1.0 + i;
			zVert = 1.0 + j;
			for (; k < 6 ; k++) // esquerda
			{
				zAng1 = 0.3 * cos( k * CONST_PI/8 ) + zCentroCilindro;
				xAng1 = 0.3 * sin( k * CONST_PI/8 ) + xCentroCilindro;
				zAng2 = 0.3 * cos( (k+1) * CONST_PI/8 ) + zCentroCilindro;
				xAng2 = 0.3 * sin( (k+1) * CONST_PI/8 ) + xCentroCilindro;

				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert - zStep );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert - zStep );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Faces laterais do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );
				
				/* Cada vertice da face lateral do cilindro tem um versor normal : Met. de GOURAUD */
				/* Esse versor resulta de normalizar o vector posicao de cada vertice */
				for (c = 1; c <= 6; c++) {
					pModelo->normals[iVertex-c] = cloneVector( pModelo->vertices[iVertex-c] );
					converterParaVersor( pModelo->normals[iVertex-c] );
				}

				/* Topo do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xCentroCilindro, 1.2, zCentroCilindro );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				zVert -= zStep;
			}
			xVert = 1.0 + i;
			zVert = 0.0 + j;
			for (; k < 10 ; k++) // cima
			{
				zAng1 = 0.3 * cos( k * CONST_PI/8 ) + zCentroCilindro;
				xAng1 = 0.3 * sin( k * CONST_PI/8 ) + xCentroCilindro;
				zAng2 = 0.3 * cos( (k+1) * CONST_PI/8 ) + zCentroCilindro;
				xAng2 = 0.3 * sin( (k+1) * CONST_PI/8 ) + xCentroCilindro;

				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xVert - xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Faces laterais do cilindro CW */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Cada vertice da face lateral do cilindro tem um versor normal : Met. de GOURAUD */
				/* Esse versor resulta de normalizar o vector posicao de cada vertice */
				for (c = 1; c <= 6; c++) {
					pModelo->normals[iVertex-c] = cloneVector( pModelo->vertices[iVertex-c] );
					converterParaVersor( pModelo->normals[iVertex-c] );
				}

				/* Topo do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xCentroCilindro, 1.2, zCentroCilindro );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				xVert -= xStep;
			}
			xVert = 0.0 + i;
			zVert = 0.0 + j;
			for (; k < 14 ; k++) // esquerda
			{
				zAng1 = 0.3 * cos( k * CONST_PI/8 ) + zCentroCilindro;
				xAng1 = 0.3 * sin( k * CONST_PI/8 ) + xCentroCilindro;
				zAng2 = 0.3 * cos( (k+1) * CONST_PI/8 ) + zCentroCilindro;
				xAng2 = 0.3 * sin( (k+1) * CONST_PI/8 ) + xCentroCilindro;

				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert + zStep );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert + zStep );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Faces laterais do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Cada vertice da face lateral do cilindro tem um versor normal : Met. de GOURAUD */
				/* Esse versor resulta de normalizar o vector posicao de cada vertice */
				for (c = 1; c <= 6; c++) {
					pModelo->normals[iVertex-c] = cloneVector( pModelo->vertices[iVertex-c] );
					converterParaVersor( pModelo->normals[iVertex-c] );
				}

				/* Topo do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xCentroCilindro, 1.2, zCentroCilindro );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				zVert += zStep;
			}
			xVert = 0.0 + i;
			zVert = 1.0 + j;
			for (; k < 16 ; k++) // baixo direita
			{
				zAng1 = 0.3 * cos( k * CONST_PI/8 ) + zCentroCilindro;
				xAng1 = 0.3 * sin( k * CONST_PI/8 ) + xCentroCilindro;
				zAng2 = 0.3 * cos( (k+1) * CONST_PI/8 ) + zCentroCilindro;
				xAng2 = 0.3 * sin( (k+1) * CONST_PI/8 ) + xCentroCilindro;

				pModelo->vertices[iVertex++] = createVertex( xVert, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xVert + xStep, 1.0, zVert );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Faces laterais do cilindro CCW */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.0, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.0, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				/* Cada vertice da face lateral do cilindro tem um versor normal : Met. de GOURAUD */
				/* Esse versor resulta de normalizar o vector posicao de cada vertice */
				for (c = 1; c <= 6; c++) {
					pModelo->normals[iVertex-c] = cloneVector( pModelo->vertices[iVertex-c] );
					converterParaVersor( pModelo->normals[iVertex-c] );
				}

				/* Topo do cilindro */
				pModelo->vertices[iVertex++] = createVertex( xAng1, 1.2, zAng1 );
				pModelo->vertices[iVertex++] = createVertex( xAng2, 1.2, zAng2 );
				pModelo->vertices[iVertex++] = createVertex( xCentroCilindro, 1.2, zCentroCilindro );
				pModelo->faces[iFace++] = createTriangle( iVertex-3, iVertex-2, iVertex-1 );

				xVert += xStep;
			}

			zCentroCilindro += 1.0;
		}
		zCentroCilindro = 0.5;
		xCentroCilindro += 1.0;
	}

      
   /* Cada vertice tem um versor normal */
   /* Que, neste caso, e o versor normal a face triangular */
   for( i = 0; i < pModelo->numFaces; i++ )
   {
	   	/* excluir os vertices das faces laterais dos cilindros (que já têm as normais definidas através do método de Gouraud) */
		if ( pModelo->normals[indexTriangleVertex( 0, i, pModelo )] != 0 )
		{
			continue;
		}

		/* Obter os pontos definindo cada triangulo */
        /* e calcular o vector normal               */
 	    temp = triangleNormal(  
           pModelo->vertices[ indexTriangleVertex( 0, i, pModelo ) ],
           pModelo->vertices[ indexTriangleVertex( 1, i, pModelo ) ],
           pModelo->vertices[ indexTriangleVertex( 2, i, pModelo ) ] );
   
        /* Atribui-lo a cada um dos vertices */
        for( j = 0; j < 3; j++ )
        {        
           pModelo->normals[ indexTriangleVertex( j, i, pModelo ) ] = 
              cloneVector( temp );
        }
        
        free(temp);
   }
   
   /* Propriedades do material do modelo */
   /* White Plastic */
   pModelo->coefReflAmbiente[0] = 0.0;
   pModelo->coefReflAmbiente[1] = 0.0;
   pModelo->coefReflAmbiente[2] = 0.0;
   pModelo->coefReflAmbiente[3] = 1.0;
   
   pModelo->coefReflDifusa[0] = 0.55;
   pModelo->coefReflDifusa[1] = 0.55;
   pModelo->coefReflDifusa[2] = 0.55;
   pModelo->coefReflDifusa[3] = 1.0;
   
   pModelo->coefReflEspecular[0] = 0.7;
   pModelo->coefReflEspecular[1] = 0.7;
   pModelo->coefReflEspecular[2] = 0.7;
   pModelo->coefReflEspecular[3] = 1.0;
   
   /* Coef. de Phong - Algum brilho */
   pModelo->coefDePhong[0] = 32.0;
   
   /* Parametros globais de transformacao */
   pModelo->translX = 0.0;
   pModelo->translY = 0.0;
   pModelo->translZ = 0.0;
   pModelo->rotAngXX = 0;
   pModelo->rotAngYY = 0;
   pModelo->rotAngZZ = 0;
   pModelo->factorX = 1.0;
   pModelo->factorY = 1.0;
   pModelo->factorZ = 1.0;

   /* Controlos da animacao */
   pModelo->rotationOnXX = 0;
   pModelo->rotationOnYY = 0;
   pModelo->rotationOnZZ = 0;

   /* Devolver o ponteiro para o registo criado */
   return pModelo;
}

/* Draw a 10x10 grid */
void drawGrid( void )
{
	int i = 0;

	if(!toggleGrid)	return;
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0); 
		for(i=0;i<=50;i++) 
		{
			glVertex3f(i-25,0,-25);
			glVertex3f(i-25,0,25);
			glVertex3f(-25,0,i-25);
			glVertex3f(25,0,i-25);
		};
	glEnd();
	glEnable(GL_LIGHTING);
}

/*
 * drawAxes()
 * ------
 * Draw the axes
 */
void drawAxes() 
{
	double len = 2.0;
	if (toggleAxes) {
		glDisable(GL_LIGHTING);
		/*  Length of axes */
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(len,0,0);
			glVertex3d(0,0,0);
			glVertex3d(0,len,0);
			glVertex3d(0,0,0);
			glVertex3d(0,0,len);
		glEnd();
		/*  Label axes */
		glEnable(GL_LIGHTING);
	}
}

/*
 *  drawShape()
 *  ------
 *  Draw the GLUT shape
 */
void drawShape()
{
	/*  Cube vertices */
	GLfloat vertA[3] = { 0.5, 0.5, 0.5};
	GLfloat vertB[3] = {-0.5, 0.5, 0.5};
	GLfloat vertC[3] = {-0.5,-0.5, 0.5};
	GLfloat vertD[3] = { 0.5,-0.5, 0.5};
	GLfloat vertE[3] = { 0.5, 0.5,-0.5};
	GLfloat vertF[3] = {-0.5, 0.5,-0.5};
	GLfloat vertG[3] = {-0.5,-0.5,-0.5};
	GLfloat vertH[3] = { 0.5,-0.5,-0.5};
	
	/* Cube */
	glBegin(GL_QUADS);
		/* front => ABCD yellow */
		glColor3f(1.0,1.0,0.0);
		glVertex3fv(vertA);
		glVertex3fv(vertB);
		glVertex3fv(vertC);
		glVertex3fv(vertD);

		/* back => FEHG red */
		glColor3f(1.0,0.0,0.0);
		glVertex3fv(vertF);
		glVertex3fv(vertE);
		glVertex3fv(vertH);
		glVertex3fv(vertG);
		
		/* right => EADH green */
		glColor3f(0.0,1.0,0.0);
		glVertex3fv(vertE);
		glVertex3fv(vertA);
		glVertex3fv(vertD);
		glVertex3fv(vertH);
		
		/* left => BFGC blue */
		glColor3f(0.0,0.0,1.0);
		glVertex3fv(vertB);
		glVertex3fv(vertF);
		glVertex3fv(vertG);
		glVertex3fv(vertC);
		
		/* top => EFBA turquoise */
		glColor3f(0.0,1.0,1.0);
		glVertex3fv(vertE);
		glVertex3fv(vertF);
		glVertex3fv(vertB);
		glVertex3fv(vertA);
		
		/* bottom => DCGH pink */
		glColor3f(1.0,0.0,1.0);
		glVertex3fv(vertD);
		glVertex3fv(vertC);
		glVertex3fv(vertG);
		glVertex3fv(vertH);
	glEnd();
}
/* ------------------------------------------------------------------ */
