/*
 * rw.h
 * RW header file - it provides the functions to read and write models 
 * in files 
 *
 * badpointer - Nov/2011
 */

#ifndef _rw_h
#define _rw_h

/* public methods */
/* ------------------------------------------------------------------ */

/* allows the user to write a model in a file */
int writeConstruction( void );

/* allows the user to read a model from a file */
int readConstruction( void );

/* ------------------------------------------------------------------ */

#endif
