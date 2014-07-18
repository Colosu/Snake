#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "include\SDL2\SDL.h"
#include "Objetos.h"
#include "Mapa.h"
#include "Movimiento.h"
#include "Ventana.h"
#include "Presentacion.h"



int main() {

	tMapa mapa;
	tSerpiente serpiente;
	SDL_Window *ventana = NULL;
	SDL_Renderer *renderizado = NULL;
	SDL_Texture *bordes;
	SDL_Texture *manzanas;
	SDL_Texture *serpientes;
	string direccion;
	bool iniciado;

	//idioma();
	srand(time(NULL));
	limpiar();

	iniciado = inicializarSDL(ventana, renderizado);

	direccion = "resources/";

	bordes = cargarTextura(direccion + "borde.bmp", renderizado);
	manzanas = cargarTextura(direccion + "manzana.bmp", renderizado);
	serpientes = cargarTextura(direccion + "serpiente.bmp", renderizado);

	if (bordes == NULL || manzanas == NULL || serpientes == NULL) {

		iniciado = false;
	}

	if (iniciado) {

		inicializarSerpiente(serpiente);
		mapa = inicializarMapa(serpiente);

		mostrarMapa(mapa, renderizado, bordes, manzanas, serpientes);

		while (serpiente.contador > 0) {

			mover(mapa, serpiente, cin);
			limpiar();
			mostrarMapa(mapa, renderizado, bordes, manzanas, serpientes);
		}

		eliminarMapa(mapa);
	}

	SDL_DestroyTexture(bordes);
	SDL_DestroyTexture(manzanas);
	SDL_DestroyTexture(serpientes);

	SDL_DestroyRenderer(renderizado);

	SDL_DestroyWindow(ventana);

	SDL_Quit();
	return 0;
}