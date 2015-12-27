/*
 * dataStructures.c
 * DATASTRUCTURES implementation file - contains the code to manage
 * structures
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "dataStructs.h"
/* ----------------------------------------------------------------------- */


/* Funcoes auxiliares --- VERTICES */

point3D createVertex( GLfloat x, GLfloat y, GLfloat z )
{
    point3D vertice = (point3D) calloc( 3, sizeof( GLfloat ) );
    
    vertice[0] = x;
    vertice[1] = y;
    vertice[2] = z;
    
    return vertice;
}

point3D cloneVertex( point3D vert )
{
    point3D vertice = (point3D) calloc( 3, sizeof( GLfloat ) );
    
    vertice[0] = vert[0];
    vertice[1] = vert[1];
    vertice[2] = vert[2];
    
    return vertice;
}

void imprimeVertice( point3D vert )
{
    printf( "Vertice : %f %f %f\n", vert[0], vert[1], vert[2] );
}

point3D createMiddlePoint( point3D p1, point3D p2 )
{
    point3D vertice = (point3D) calloc( 3, sizeof( GLfloat ) );
    
    vertice[0] = ( p1[0] + p2[0] ) / 2.0;
    vertice[1] = ( p1[1] + p2[1] ) / 2.0;
    vertice[2] = ( p1[2] + p2[2] ) / 2.0;
    
    return vertice;
}
 
/* Funcoes auxiliares --- VECTORES */
vector3D createVector( GLfloat x, GLfloat y, GLfloat z )
{
    vector3D vect = (vector3D) calloc( 3, sizeof( GLfloat ) );

    vect[0] = x;
    vect[1] = y;
    vect[2] = z;
    
    return vect;
}

vector3D cloneVector( vector3D vect )
{
    vector3D v = (vector3D) calloc( 3, sizeof( GLfloat ) );
    
    v[0] = vect[0];
    v[1] = vect[1];
    v[2] = vect[2];
    
    return v;
}

vector3D constroiVector( point3D p1, point3D p2 )
{
    vector3D v = (vector3D) calloc( 3, sizeof( GLfloat ) );
	int i;
	
	/* v = p2 - p1 */
	for( i = 0; i < 3; i++ )
		v[i] = p2[i] - p1[i];

	return v;
}

void imprimeVector( vector3D vect )
{
    printf( "Vector : %f %f %f\n", vect[0], vect[1], vect[2] );
}

GLfloat normaDeVector( vector3D v )
{
	GLfloat aux = 0.0;

	int i;
	for( i = 0; i < 3; i++ )
		aux += v[i] * v[i];

	return sqrt( aux );
}

void converterParaVersor( vector3D v )
{
	GLfloat norma = normaDeVector( v );
	int i;

	if( norma > 0.0 )
	{
		for( i = 0; i < 3; i++ )
			v[i] /= norma;
	}
}

vector3D produtoVectorial( vector3D v1, vector3D v2 )
{
    vector3D res = (vector3D) calloc( 3, sizeof( GLfloat ) );
	
	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = - ( v1[0] * v2[2] - v1[2] * v2[0] );
	res[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return res;
}

vector3D sumOfVectors( vector3D a, vector3D b )
{
	vector3D v = (vector3D) calloc( 3, sizeof( GLfloat ) );
	int i;

	/* v = a + b */
	for( i = 0; i < 3; i++ )
		v[i] = a[i] + b[i];

	return v;
}

/* Funcoes auxiliares --- Faces TRIANGULARES */
triangle createTriangle( GLint ind1, GLint ind2, GLint ind3 )
{
    /* Pontos dados no sentido anti-horario */
    triangle q = (triangle) calloc( 3, sizeof( GLint ) );

    q[0] = ind1;
    q[1] = ind2;
    q[2] = ind3;
    
    return q;
}

GLint indexTriangleVertex( GLint i, GLint q, modelPointer p )
{
    /* Usar a estrutura de dados para obter o indice no 
       array global de vertices  para o 
       i-esimo [0,1,2] vertice de um triangulo de indice q */
    /* Ponteiro para o vertice */
    
    return p->faces[q][i];
}

vector3D triangleNormal( point3D p1, point3D p2, point3D p3 )
{
	/* Pontos dados no sentido anti-horário */

	vector3D v1 = constroiVector( p1, p2 );
	vector3D v2 = constroiVector( p1, p3 );
	vector3D n = produtoVectorial( v1, v2 );

	converterParaVersor( n );
	
	free( v1 );
	free( v2 );

	return n;
}
              
/* ----------------------------------------------------------------------- */
