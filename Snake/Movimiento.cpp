#include <iostream>
using namespace std;
#include <cstdlib>
#include "Mapa.h"
#include "Objetos.h"
#include "Presentacion.h"

void mover(tMapa &mapa, tSerpiente &serpiente, SDL_Event evento) {

	if (evento.key.keysym.sym == SDLK_a) {

		serpiente.columna--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_w) {

		serpiente.fila--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_d) {

		serpiente.columna++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_s) {

		serpiente.fila++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	}
}