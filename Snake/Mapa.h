#ifndef MAPA_H
#define MAPA_H

#include "include\SDL2\SDL.h"
#include "Objetos.h"

const int FILAS = 42;
const int COLUMNAS = 42;

typedef struct {

	int tipo;
	bool manzana;
	bool serpiente;
} tCasilla;

typedef struct {

	tCasilla **mapa;
} tMapa;

tMapa inicializarMapa(tSerpiente &serpiente);
void eliminarMapa(tMapa &mapa);
void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio);
void mostrarMapa(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *agujeros, SDL_Texture *manzanas, SDL_Texture *serpientes, SDL_Rect clipsSerpiente[12]);
void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna);
void actualizarMapa(tMapa &mapa);
void generarManzana(tMapa &mapa);

#endif