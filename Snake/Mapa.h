#ifndef MAPA_H
#define MAPA_H

#include "include\SDL2\SDL.h"
#include "Objetos.h"

const int FILAS = 20;
const int COLUMNAS = 20;

typedef struct {

	int tipo;
	bool animal;
	bool noe;
} tCasilla;

typedef struct {

	tCasilla **mapa;
} tMapa;

tMapa inicializarMapa(tNoe &noe, tAnimal &animal1, tAnimal &animal2);
void eliminarMapa(tMapa &mapa);
void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio, SDL_Texture *iniciar, SDL_Texture *titulo);
void mostrarMapa(tMapa mapa, tNoe noe, tAnimal animal1, tAnimal animal2, SDL_Renderer *renderizado, SDL_Texture *puntuacion, SDL_Texture *puntos, SDL_Texture *agua, SDL_Texture *manzanas, SDL_Texture *noes, SDL_Rect clipsNoe[4], SDL_Texture *animales[3]);
void actualizarMapa(tMapa &mapa, tNoe &noe, tAnimal &animal1, tAnimal &animal2, int fila, int columna);
void actualizarMapa(tMapa &mapa, tNoe &noe);
void generarAnimal(tMapa &mapa, tAnimal &animal);

#endif