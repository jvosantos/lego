/*
 * rendering.c
 * RENDERING implementation file.
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include <GL/glut.h>
#include "dataStructs.h"
#include "rendering.h"
#include "globals.h" 
#include "models.h"
#include "materialProps.h"
/* ------------------------------------------------------------------ */

/* private methods */
/* ------------------------------------------------------------------ */
//insert private methods here
void deployModel(modelPointer pModel)
{
	int i, j, index;

    /* Propriedades do material do modelo */
    glMaterialfv( GL_FRONT, GL_AMBIENT, pModel->coefReflAmbiente );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, pModel->coefReflDifusa );
    glMaterialfv( GL_FRONT, GL_SPECULAR, pModel->coefReflEspecular );
    glMaterialfv( GL_FRONT, GL_SHININESS, pModel->coefDePhong );

	/* save current transf matrix */
	glPushMatrix();
	
	/* apply transformations relatively to the center of mass and in reverse order */
	glTranslatef(pModel->translX, pModel->translY, pModel->translZ);
	glRotatef(pModel->rotAngZZ, 0.0, 0.0, 1.0);
	glRotatef(pModel->rotAngYY, 0.0, 1.0, 0.0);
	glRotatef(pModel->rotAngZZ, 1.0, 0.0, 0.0);
	glScalef(pModel->factorX, pModel->factorY, pModel->factorZ);


	/* rendering using dataStructs */
	glBegin(GL_TRIANGLES);
	for(i=0; i<pModel->numFaces; i++){
		for(j=0; j<3; j++){
			index = indexTriangleVertex(j, i, pModel);
			glNormal3fv(pModel->normals[index]);
			glVertex3fv(pModel->vertices[index]);
		}
	}
	glEnd();

	glPopMatrix();
}

void placeSpotlight(spotlightPointer p_Spotlight)
{
	if(p_Spotlight->spotlightIsOn)
	{
		glEnable(p_Spotlight->light);
	
		glLightfv( p_Spotlight->light, GL_AMBIENT, p_Spotlight->compAmbiente );
		glLightfv( p_Spotlight->light, GL_DIFFUSE, p_Spotlight->compDifusa );
		glLightfv( p_Spotlight->light, GL_SPECULAR, p_Spotlight->compEspecular );
	}
	else
	{
		glDisable( p_Spotlight->light );
	}

	glPushMatrix();

	glTranslatef( p_Spotlight->translX, p_Spotlight->translY, p_Spotlight->translZ );

	glRotatef( p_Spotlight->rotAngZZ, 0.0, 0.0, 1.0 );
	glRotatef( p_Spotlight->rotAngYY, 0.0, 1.0, 0.0 );
	glRotatef( p_Spotlight->rotAngXX, 1.0, 0.0, 0.0 );

	glLightfv( p_Spotlight->light, GL_POSITION, p_Spotlight->position );

	glPopMatrix();
}

void drawSpotlight( spotlightPointer p_Spotlight )
{
	if(!(p_Spotlight->spotlightIsOn))
		return;

	glPushMatrix();

	glTranslatef( p_Spotlight->translX, p_Spotlight->translY, p_Spotlight->translZ );

	glRotatef( p_Spotlight->rotAngZZ, 0.0, 0.0, 1.0 );
	glRotatef( p_Spotlight->rotAngYY, 0.0, 1.0, 0.0 );
	glRotatef( p_Spotlight->rotAngXX, 1.0, 0.0, 0.0 );

	glDisable(GL_LIGHTING);

	glColor4fv( p_Spotlight->compDifusa );
	glTranslatef( p_Spotlight->position[0], p_Spotlight->position[1], p_Spotlight->position[2] );
	glutSolidSphere( 0.05, 10, 10 );

	glEnable(GL_LIGHTING);
	glPopMatrix();
}
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void deployPieces( void )
{
	int i;
	glPushMatrix();

	drawGrid();
	drawAxes();

	glShadeModel( GL_SMOOTH );
	if(tmpModel != NULL)
		deployModel(tmpModel);

	glShadeModel( GL_SMOOTH );
	for(i = 0; i < numberModels; i++)
		deployModel(models[i]);

	glPopMatrix();
}

void deploySpotLights( void )
{
	placeSpotlight( pSpotlight1 );
	drawSpotlight( pSpotlight1 );

	placeSpotlight( pSpotlight2 );
	drawSpotlight( pSpotlight2 );
	
	placeSpotlight( pSpotlight3 );
	drawSpotlight( pSpotlight3 );
	
	placeSpotlight( pSpotlight4 );
	drawSpotlight( pSpotlight4 );
	
	placeSpotlight( pSpotlight5 );
	drawSpotlight( pSpotlight5 );
}

/* ------------------------------------------------------------------ */
