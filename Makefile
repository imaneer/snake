CC=gcc
CFLAGS=-ansi -pedantic -Wall
LDFLAGS=-lncurses
OBJ=Main.o Case.o Serpent.o Pomme.c Monde.o Interface.o

Tp5: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

Main.o: Main.c Monde.h Interface.h

Case.o: Case.c Case.h

Serpent.o: Serpent.c Serpent.h Case.h

Pomme.o: Pomme.c Pomme.h Case.h

Monde.o: Monde.c Monde.h Case.h Serpent.h Pomme.h

Interface.o: Interface.c Interface.h Monde.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Tp5
