CC=gcc
GLFLAGS=-I/usr/local/include -L/usr/local/lib -lGL -lglut -lGLU -Wall
SOURCES=callbacks.c init.c lego.c rendering.c viewing3D.c menus.c models.c dataStructs.c spotlights.c materialProps.c rw.c consoleIO.c
HEADERS=callbacks.h globals.h init.h rendering.h viewing3D.h menus.h models.h dataStructs.h spotlights.h materialProps.h rw.h consoleIO.h
OBJECTS=$(SOURCES:.c=.o)
EXEC=lego

all:	$(SOURCES) $(HEADERS) $(EXEC)

$(EXEC):	$(OBJECTS)
	@echo Compiling $(EXEC)...
	gcc $(GLFLAGS) $^ -o $@
	@echo Success...

clean:
	@echo Cleaning objects...	
	rm -rf $(OBJECTS)

cleanall:
	make clean
	@echo Cleaning executables...
	rm -rf $(EXEC)
