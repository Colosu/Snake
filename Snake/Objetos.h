#ifndef OBJETOS_H
#define OBJETOS_H

const int CASILLA_ANCHO = 15;
const int CASILLA_ALTO = 15;

typedef enum {Norte, Sur, Este, Oeste} tDireccion;

typedef struct {
	int fila;
	int columna;
	int contador;
	tDireccion nuevaDireccion;
	tDireccion ultimaDireccion;
} tSerpiente;

void inicializarSerpiente(tSerpiente &serpiente, SDL_Rect clipsSerpiente[12]);

#endif