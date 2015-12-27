/*
 * menus.h
 * MENUS implementation file - contains the code to create menus and 
 * its structures 
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdlib.h>
#include <GL/glut.h>
#include "globals.h"
#include "rw.h"
#include "models.h"
#include "menus.h"
#include "viewing3D.h"
#include "init.h"
/* ------------------------------------------------------------------ */

/* Structures used for menus */
/* ------------------------------------------------------------------ */
/* auxiliar type for menu */
typedef struct menuItemStruct
{
	/* item text */
	char *item; 
	/* returned value */
	char val;
} menuItemStruct;

/* Menu1 - Associated with the right button */
static menuItemStruct menu1[]={
	"draw", '-',
	"spotLights", '-',
	"store construction", 's',
	"load construction", 'l',
	"restart", 'r',
	"exit", 'x',
};
int numItensMenu1 = sizeof(menu1) / sizeof(menuItemStruct);

/* SubMenu1 - Associated to the draw */
static menuItemStruct subMenuDraw[]={
	"grid", 'g',
	"piece 1-1", '1',
	"piece 1-2", '2',
	"piece 1-3", '3',
	"piece 1-4", '4',
	"piece 2-2", '5',
	"piece 2-3", '6',
	"piece 2-4", '7',
	"piece 3-3", '8',
	"piece 3-4", '9',
	"piece 4-4", 'a',
};

int numItensSubMenuDraw = sizeof(subMenuDraw)/sizeof(menuItemStruct);

static menuItemStruct subMenuSpotlights[]={
	"spotlight 1", '-',
	"spotlight 2", '-',
	"spotlight 3", '-',
	"spotlight 4", '-',
	"spotlight 5", '-',
};
int numItensSubMenuSpotlights = sizeof(subMenuSpotlights)/sizeof(menuItemStruct);

/* SubMenu2 - Associated to the spotlight1 */
static menuItemStruct subMenuSpotlight1[]={
	"toggle", 't',
	"rotate", 'r',
};
int numItensSubMenuSpotlight1 = sizeof(subMenuSpotlight1)/sizeof(menuItemStruct);

/* SubMenu2 - Associated to the spotlight2 */
static menuItemStruct subMenuSpotlight2[]={
	"toggle", 't',
	"rotate", 'r',
};
int numItensSubMenuSpotlight2 = sizeof(subMenuSpotlight2)/sizeof(menuItemStruct);

/* SubMenu2 - Associated to the spotlight3 */
static menuItemStruct subMenuSpotlight3[]={
	"toggle", 't',
	"rotate", 'r',
};
int numItensSubMenuSpotlight3 = sizeof(subMenuSpotlight3)/sizeof(menuItemStruct);

/* SubMenu2 - Associated to the spotlight4 */
static menuItemStruct subMenuSpotlight4[]={
	"toggle", 't',
	"rotate", 'r',
};
int numItensSubMenuSpotlight4 = sizeof(subMenuSpotlight4)/sizeof(menuItemStruct);

/* SubMenu2 - Associated to the spotlight5 */
static menuItemStruct subMenuSpotlight5[]={
	"toggle", 't',
	"rotate", 'r',
};
int numItensSubMenuSpotlight5 = sizeof(subMenuSpotlight5)/sizeof(menuItemStruct);


/* ------------------------------------------------------------------ */

/* private methods */
/* ------------------------------------------------------------------ */
/* Callback function for menu1 - leftButton */

void mySubMenuDraw( int i )
{
	switch(subMenuDraw[i].val)
	{
		case 'g':
			toggleGrid = 1-toggleGrid;
			break;
		case '1':
			tmpModel = createLego(1, 1);
			break;
		case '2':
			tmpModel = createLego(1, 2);
			break;
		case '3':
			tmpModel = createLego(1, 3);
			break;
		case '4':
			tmpModel = createLego(1, 4);
			break;
		case '5':
			tmpModel = createLego(2, 2);
			break;
		case '6':
			tmpModel = createLego(2, 3);
			break;
		case '7':
			tmpModel = createLego(2, 4);
			break;
		case '8':
			tmpModel = createLego(3, 3);
			break;
		case '9':
			tmpModel = createLego(3, 4);
			break;
		case 'a':
			tmpModel = createLego(4, 4);
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlight1( int i )
{
	switch(subMenuSpotlight1[i].val)
	{
		case 't':
			pSpotlight1->spotlightIsOn = (pSpotlight1->spotlightIsOn)?0:1;
			break;
		case 'r':
			if(pSpotlight1->rotationOnYY)
			{
				pSpotlight1->rotationOnYY = 0;
				pSpotlight1->position[0] = 0.0;
			}
			else
			{
				pSpotlight1->rotationOnYY = 1;
				pSpotlight1->position[0] = 10.0;
			}
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlight2( int i )
{
	switch(subMenuSpotlight2[i].val)
	{
		case 't':
			pSpotlight2->spotlightIsOn = (pSpotlight2->spotlightIsOn)?0:1;
			break;
		case 'r':
			if(pSpotlight2->rotationOnYY)
			{
				pSpotlight2->rotationOnYY = 0;
				pSpotlight2->position[0] = 0.0;
			}
			else
			{
				pSpotlight2->rotationOnYY = 1;
				pSpotlight2->position[0] = 10.0;
			}
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlight3( int i )
{
	switch(subMenuSpotlight3[i].val)
	{
		case 't':
			pSpotlight3->spotlightIsOn = (pSpotlight3->spotlightIsOn)?0:1;
			break;
		case 'r':
			if(pSpotlight3->rotationOnYY)
			{
				pSpotlight3->rotationOnYY = 0;
				pSpotlight3->position[0] = 0.0;
			}
			else
			{
				pSpotlight3->rotationOnYY = 1;
				pSpotlight3->position[0] = 10.0;
			}
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlight4( int i )
{
	switch(subMenuSpotlight4[i].val)
	{
		case 't':
			pSpotlight4->spotlightIsOn = (pSpotlight4->spotlightIsOn)?0:1;
			break;
		case 'r':
			if(pSpotlight4->rotationOnYY)
			{
				pSpotlight4->rotationOnYY = 0;
				pSpotlight4->position[0] = 0.0;
			}
			else
			{
				pSpotlight4->rotationOnYY = 1;
				pSpotlight4->position[0] = 10.0;
			}
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlight5( int i )
{
	switch(subMenuSpotlight5[i].val)
	{
		case 't':
			pSpotlight5->spotlightIsOn = (pSpotlight5->spotlightIsOn)?0:1;
			break;
		case 'r':
			if(pSpotlight5->rotationOnYY)
			{
				pSpotlight5->rotationOnYY = 0;
				pSpotlight5->position[0] = 0.0;
			}
			else
			{
				pSpotlight5->rotationOnYY = 1;
				pSpotlight5->position[0] = 10.0;
			}
			break;
	}
	glutPostRedisplay();
}

void mySubMenuSpotlights( int i) { return ; }

void restart( void )
{
	int i, j;
	for(i = 0; i<numberModels; i++)
	{
		for(j=0; j<models[i]->numVertices; j++)
			free(models[i]->vertices[j]);
		free(models[i]->vertices);
		for(j=0; j<models[i]->numFaces; j++)
		{
			free(models[i]->faces[j]);
			free(models[i]->normals[j]);
		}
		free(models[i]->faces);
		free(models[i]->normals);
		free(models[i]);
	}
	initVariables();
	tmpModel=NULL;
}

static void myMenuEsq( int i )
{
	switch( menu1[i].val )
	{
		case 's':
				writeConstruction();	
				break;
		case 'l':
				restart();
				readConstruction();
				writeConstruction();
				glutPostRedisplay();
				break;
		case 'r':
				restart();
				glutPostRedisplay();
				break;
		case 'x':
				exit(0);
				break;
	}

}

/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void createMenus( void )
{
	int i = 0;

	int subM1, subM2;
	int subMS1, subMS2, subMS3, subMS4, subMS5;

	subMS1 = glutCreateMenu( mySubMenuSpotlight1 );
	for(i=0; i<numItensSubMenuSpotlight1; i++)
		glutAddMenuEntry(subMenuSpotlight1[i].item, i);

	subMS2 = glutCreateMenu( mySubMenuSpotlight2 );
	for(i=0; i<numItensSubMenuSpotlight2; i++)
		glutAddMenuEntry(subMenuSpotlight2[i].item, i);

	subMS3 = glutCreateMenu( mySubMenuSpotlight3 );
	for(i=0; i<numItensSubMenuSpotlight3; i++)
		glutAddMenuEntry(subMenuSpotlight3[i].item, i);

	subMS4 = glutCreateMenu( mySubMenuSpotlight4 );
	for(i=0; i<numItensSubMenuSpotlight4; i++)
		glutAddMenuEntry(subMenuSpotlight4[i].item, i);

	subMS5 = glutCreateMenu( mySubMenuSpotlight5 );
	for(i=0; i<numItensSubMenuSpotlight5; i++)
		glutAddMenuEntry(subMenuSpotlight5[i].item, i);

/* subMenu 1 */ 
	subM1 = glutCreateMenu( mySubMenuDraw );
	for(i = 0; i < numItensSubMenuDraw; i++)
		glutAddMenuEntry(subMenuDraw[i].item, i);

/* subMenu 2*/
	subM2 = glutCreateMenu( mySubMenuSpotlights );
	glutAddSubMenu(subMenuSpotlights[0].item, subMS1);
	glutAddSubMenu(subMenuSpotlights[1].item, subMS2);
	glutAddSubMenu(subMenuSpotlights[2].item, subMS3);
	glutAddSubMenu(subMenuSpotlights[3].item, subMS4);
	glutAddSubMenu(subMenuSpotlights[4].item, subMS5);

/* Menu 1 */
	glutCreateMenu(myMenuEsq);
	glutAddSubMenu(menu1[0].item, subM1);
	glutAddSubMenu(menu1[1].item, subM2);
	for(i = 2; i < numItensMenu1; i++)
	{
		/* The items from the menu and the values returned by the callback function */
		glutAddMenuEntry( menu1[i].item, i );
	}

	
	/* Associated mouse button */
	glutAttachMenu( GLUT_RIGHT_BUTTON );

}
/* ------------------------------------------------------------------ */
