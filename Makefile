CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = 
LDFLAGS = `sdl2-config --cflags --libs` 
INCLUDES = 
EXEC = superMario_OX
SRC = main.c world.c display.c liste.c
OBJ = $(SRC:.c=.o)
all: $(EXEC)
superMario_OX: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)
