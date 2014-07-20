#include <cstdlib>
#include "Mapa.h"
#include "Objetos.h"
#include "Presentacion.h"

void mover(tMapa &mapa, tSerpiente &serpiente, const SDL_Event &evento) {

	if (evento.key.keysym.sym == SDLK_a || evento.key.keysym.sym == SDLK_LEFT) {

		serpiente.columna--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_w || evento.key.keysym.sym == SDLK_UP) {

		serpiente.fila--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_d || evento.key.keysym.sym == SDLK_RIGHT) {

		serpiente.columna++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (evento.key.keysym.sym == SDLK_s || evento.key.keysym.sym == SDLK_DOWN) {

		serpiente.fila++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	}
}