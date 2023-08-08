# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = jornal.o
     
jornal: jornal.o libfila.o
	$(CC) -o jornal jornal.o $(LDFLAGS)

jornal.o: jornal.c
	$(CC) -c $(CFLAGS) jornal.c

clean:
	rm -f $(objects) jornal


