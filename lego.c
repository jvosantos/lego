/*
 * legos.c
 * simulação / animação da construção de modelos usando peças Lego,
 * com diferentes formas e cores. O utilizador deve poder seleccionar a peça
 * que quer usar, orientá-la e posicioná-la, de modo a ir construindo um dado
 * modelo. Deverá ser possível apresentar quer diferentes vistas (pré-
 * definidas) do modelo que está a ser construído, quer posicionar o
 * observador em diferentes pontos da cena 3D. Uma possibilidade
 * interessante seria ler de ficheiro um guião que define o modo como um
 * modelo é construído e apresentar uma animação da sua construção.
 * Uso de uma estrutura de dados para as faces de um modelo
 *
 * Badpointer - Nov 2011
 */

/* "Imports" */
/* ------------------------------------------------------------------ */
#include <stdio.h>
#include <GL/glut.h>
#include "consoleIO.h"
#include "callbacks.h"
#include "init.h"
#include "menus.h"
/* ------------------------------------------------------------------ */

/* main */
/* ------------------------------------------------------------------ */
int main( int argc, char** argv )
{
	/* GLUT init */
	glutInit( &argc, argv);

	/* Inits */
	initVariables();
	initWindow();
	createMenus();
	initSpotlights();

	/* sign in callback functions */
	signInCallbackFunctions();

	/* wait for events to occur */
	howToInfo();
	glutMainLoop();
	printf("\n\n\a\aWHY?????\a\a\n\n");

	return 0;
}
/* ------------------------------------------------------------------ */
