#include <iostream>
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
	SDL_Event evento;
	bool iniciado;

	//idioma();
	srand(time(NULL));
	limpiar();

	iniciado = inicializarSDL(ventana, renderizado);

	if (iniciado) {

		inicializarSerpiente(serpiente);
		mapa = inicializarMapa(serpiente);

		mostrarMapa(mapa, cout);

		while (serpiente.contador > 0) {

			mover(mapa, serpiente, cin);
			limpiar();
			mostrarMapa(mapa, cout);
		}

		eliminarMapa(mapa);
	}

	SDL_DestroyRenderer(renderizado);

	SDL_DestroyWindow(ventana);

	SDL_Quit();
	return 0;
}