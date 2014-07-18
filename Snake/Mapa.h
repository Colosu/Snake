#ifndef MAPA_H
#define MAPA_H

#include <iostream>
using namespace std;
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
void mostrarMapa(tMapa mapa, SDL_Renderer *renderizado, SDL_Texture *bordes, SDL_Texture *manzanas, SDL_Texture *serpientes);
void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna);
void generarManzana(tMapa &mapa, tSerpiente serpiente);

#endif