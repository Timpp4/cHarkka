HT: paaohjelma.o aliohjelmat.o
	gcc paaohjelma.o aliohjelmat.o -o HT -std=c99 -Wall -pedantic -lm
aliohjelmat.o: aliohjelmat.c esittelyt.h
	gcc aliohjelmat.c -c -std=c99 -Wall -pedantic -lm
paaohjelma.o: paaohjelma.c esittelyt.h
	gcc paaohjelma.c -c -std=c99 -Wall -pedantic -lm
