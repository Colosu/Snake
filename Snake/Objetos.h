#ifndef OBJETOS_H
#define OBJETOS_H

typedef struct {
	int fila;
	int columna;
	int contador;
} tSerpiente;

void inicializarSerpiente(tSerpiente &serpiente);

#endif