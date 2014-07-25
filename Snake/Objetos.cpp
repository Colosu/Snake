#include "include\SDL2\SDL.h"
#include "Objetos.h"

void inicializarSerpiente(tSerpiente &serpiente, SDL_Rect clipsSerpiente[12]) {
	serpiente.fila = 1;
	serpiente.columna = 1;
	serpiente.contador = 1;
	serpiente.nuevaDireccion = tDireccion(0);
	serpiente.ultimaDireccion = tDireccion(0);

	for (int i = 0; i < 12; i++) {

		clipsSerpiente[i].x = (i % 3) * CASILLA_ANCHO;
		clipsSerpiente[i].y = (i / 3) * CASILLA_ALTO;
		clipsSerpiente[i].w = CASILLA_ANCHO;
		clipsSerpiente[i].h = CASILLA_ALTO;
	}
}