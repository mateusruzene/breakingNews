# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o
     
main: main.o 
	$(CC) -o main main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main


