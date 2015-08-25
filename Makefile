all:
	gcc -c main.c matEntrada.c
	gcc main.o matEntrada.o -g -o jacobiRichardson
run:
	./jacobiRichardson
