#ifndef MAPA_H
#define MAPA_H

#include "include\SDL2\SDL.h"
#include "Objetos.h"

const int FILAS = 40;
const int COLUMNAS = 40;

typedef struct {

	int tipo;
} tCasilla;

typedef struct {

	tCasilla **mapa;
} tMapa;

tMapa inicializarMapa(tSerpiente &serpiente);
void eliminarMapa(tMapa &mapa);
void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio);
void mostrarMapa(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *bordes, SDL_Texture *manzanas, SDL_Texture *cabezaSerpiente, SDL_Texture *serpientes);
void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna);
void generarManzana(tMapa &mapa);

#endif