all: viaje

viaje: viaje.tab.c lex.yy.c simulacion.c
	gcc -o viaje viaje.tab.c lex.yy.c simulacion.c -lfl -lm

viaje.tab.c viaje.tab.h: viaje.y
	bison -d viaje.y

lex.yy.c: viaje.l viaje.tab.h
	flex viaje.l

clean:
	rm -f viaje viaje.tab.c viaje.tab.h lex.yy.c
