#ifndef SERPIENTE_H
#define SERPIENTE_H

typedef struct {
	int fila;
	int columna;
	int contador;
} tSerpiente;

void inicializarSerpiente(tSerpiente &serpiente);

#endif