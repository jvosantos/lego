/*
 * callbacks.c
 * CALLBACKS implementation file - contains the code used to sign in 
 * callbacks.
 *
 * badpointer - Nov/2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "callbacks.h"
#include "viewing3D.h"
#include "globals.h" 
#include "rendering.h"
#include "materialProps.h"

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/* ------------------------------------------------------------------ */

/* private methods */
/* ------------------------------------------------------------------ */
void myDisplay( void )
{
	/*  Clear the image */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/*  Enable Z-buffering in OpenGL */
	glEnable(GL_DEPTH_TEST);

	/*  Reset previous transforms */
	glLoadIdentity();

	/*  Perspective - set eye position */
	if (toggleMode) {
	    double Ex = -2*dim*Sin(th)*Cos(ph);
		double Ey = +2*dim        *Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);
		/* camera/eye position, aim of camera lens, up-vector */
		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	}
	/*  Orthogonal - set world orientation */
	else {
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}

	/* Draw */
	deploySpotLights();
	deployPieces();

	/*  Flush and swap */
	glFlush();
	glutSwapBuffers();
}

void myKeyboard( unsigned char key, int x, int y )
{
	/*  Exit on ESC */
	switch(key)
	{
		case 27:	
					exit(0);
					break;
		case 'a':	
					toggleAxes = 1-toggleAxes;
					break;
		case 'm':	
					toggleMode = 1-toggleMode;
					break;
		case 'g':	
					toggleGrid = 1-toggleGrid;
					break;
		case '+':
					fov--;
					break;
		case '-':
					fov++;
					break;
		case 'D':	
					right+=0.1;
					left-=0.1;
					top+=0.1;
					bottom-=0.1;
					zNear+=0.1;
					zFar-=0.1;
					dim+=0.1;
					break;
		case 'd':
					if(dim>1){
						right-=0.1;
						left+=0.1;
						top-=0.1;
						bottom+=0.1;
						zNear-=0.1;
						zFar+=0.1;
						dim-=0.1;
					}
					break;
		case 'k':
					if(tmpModel != NULL ) tmpModel->translZ += -1.0;
					break;
		case 'i':
					if(tmpModel != NULL ) tmpModel->translZ += 1.0;
					break;
		case 'j':
					if(tmpModel != NULL ) tmpModel->translX += -1.0;
					break;
		case 'l':
					if(tmpModel != NULL ) tmpModel->translX += 1.0;
					break;
		case 'u':
					if(tmpModel != NULL ) tmpModel->translY += -1.0;
					break;
		case 'o':
					if(tmpModel != NULL ) tmpModel->translY += 1.0;
					break;
		case '1':
					if(tmpModel != NULL ) paintPlasticRed(tmpModel);	
					break;
		case '2':
					if(tmpModel != NULL ) paintPlasticYellow(tmpModel);	
					break;
		case '3':
					if(tmpModel != NULL ) paintPlasticWhite(tmpModel);	
					break;
		case '4':
					if(tmpModel != NULL ) paintPlasticGreen(tmpModel);	
					break;
		case '5':
					if(tmpModel != NULL ) paintPlasticCyan(tmpModel);	
					break;
		case 'r':
					if(tmpModel != NULL ) tmpModel->rotAngYY += 90;
					if(tmpModel->rotAngXX >= 360) tmpModel->rotAngXX -= 360;
					break;
		case 'R':
					if(tmpModel != NULL ) tmpModel->rotAngYY -= 90;
					if( tmpModel != NULL && tmpModel->rotAngXX <= -360) tmpModel->rotAngXX += 360;
					break;
		case 13:
					if(tmpModel != NULL && numberModels<100) models[numberModels++] = tmpModel;
					tmpModel = NULL;
					break;
	}

	project();
	glutPostRedisplay();
}

/* Callback for arrow keys */
void mySpecialKeys( int key, int x, int y )
{
	/* detect special keys */
	switch( key )
	{
		/*  Left arrow key - decrease azimuth by 5 degrees */
		case GLUT_KEY_LEFT:		th-=5;	break;
		/*  Right arrow key - increase azimuth by 5 degrees */
		case GLUT_KEY_RIGHT:	th+=5;	break;
		/*  Down arrow key - decrease elevation by 5 degrees */
		case GLUT_KEY_DOWN:		ph-=5;	break;
		/*  Up arrow key - increase elevation by 5 degrees */
		case GLUT_KEY_UP:		ph+=5;	break;
	}

	th %= 360;
	ph %= 360;

	project();
	glutPostRedisplay();
}

void myReshape( int width, int height )
{
	windowWidth = width;
	windowHeight = height;
	/* define new transf window/viewport, updating windows dimensions*/
	transfWindowViewport();
}	

void myIdle ( void )
{
	if(pSpotlight1->rotationOnYY){
		pSpotlight1->rotAngYY+=1;
		if(pSpotlight1->rotAngYY >= 360) pSpotlight1->rotAngYY-=360;
	}
	if(pSpotlight2->rotationOnYY){
		pSpotlight2->rotAngYY+=1;
		if(pSpotlight2->rotAngYY >= 360) pSpotlight1->rotAngYY-=360;
	}
	if(pSpotlight3->rotationOnYY){
		pSpotlight3->rotAngYY+=1;
		if(pSpotlight3->rotAngYY >= 360) pSpotlight1->rotAngYY-=360;
	}
	if(pSpotlight4->rotationOnYY){
		pSpotlight4->rotAngYY+=1;
		if(pSpotlight4->rotAngYY >= 360) pSpotlight1->rotAngYY-=360;
	}
	if(pSpotlight5->rotationOnYY){
		pSpotlight5->rotAngYY+=1;
		if(pSpotlight5->rotAngYY >= 360) pSpotlight1->rotAngYY-=360;
	}
	if(pSpotlight1->rotationOnYY || pSpotlight2->rotationOnYY || pSpotlight3->rotationOnYY || pSpotlight4->rotationOnYY || pSpotlight5->rotationOnYY)
		glutPostRedisplay();

}
/* ------------------------------------------------------------------ */

/* public methods */
/* ------------------------------------------------------------------ */
void signInCallbackFunctions( void )
{
	glutDisplayFunc( myDisplay );
	glutIdleFunc( myIdle );
	glutKeyboardFunc( myKeyboard );
	glutReshapeFunc( myReshape );
	glutSpecialFunc( mySpecialKeys );
}
/* ------------------------------------------------------------------ */
