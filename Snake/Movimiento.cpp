#include <cstdlib>
#include "Mapa.h"
#include "Objetos.h"
#include "Presentacion.h"

void actualizarNoe(tNoe &noe);

void mover(tMapa &mapa, tNoe &noe, tAnimal &animal, const SDL_Event &evento) {

	if (evento.key.keysym.sym == SDLK_a || evento.key.keysym.sym == SDLK_LEFT) {

		actualizarNoe(noe);
		noe.posicion[1]--;
		noe.direccion = tDireccion(3);
		actualizarMapa(mapa, noe, animal, noe.posicion[0], noe.posicion[1]);
	} else if (evento.key.keysym.sym == SDLK_w || evento.key.keysym.sym == SDLK_UP) {

		actualizarNoe(noe);
		noe.posicion[0]--;
		noe.direccion = tDireccion(0);
		actualizarMapa(mapa, noe, animal, noe.posicion[0], noe.posicion[1]);
	} else if (evento.key.keysym.sym == SDLK_d || evento.key.keysym.sym == SDLK_RIGHT) {

		actualizarNoe(noe);
		noe.posicion[1]++;
		noe.direccion = tDireccion(2);
		actualizarMapa(mapa, noe, animal, noe.posicion[0], noe.posicion[1]);
	} else if (evento.key.keysym.sym == SDLK_s || evento.key.keysym.sym == SDLK_DOWN) {

		actualizarNoe(noe);
		noe.posicion[0]++;
		noe.direccion = tDireccion(1);
		actualizarMapa(mapa, noe, animal, noe.posicion[0], noe.posicion[1]);
	}
}

void actualizarNoe(tNoe &noe) {

	tCadena anterior, posterior;

	for (int I = 1; I < (noe.contador - 1); I++) {

		anterior = noe.primero;
		posterior = noe.primero;

		for (int i = 0; i < (noe.contador - (I + 1)); i++) {

			anterior = anterior->siguiente;
		}

		for (int i = 0; i < (noe.contador - (I + 2)); i++) {

			posterior = posterior->siguiente;
		}

		anterior->posicion[0] = posterior->posicion[0];
		anterior->posicion[1] = posterior->posicion[1];
		anterior->direccion = posterior->direccion;
	}

	if (noe.contador > 1) {

		noe.primero->posicion[0] = noe.posicion[0];
		noe.primero->posicion[1] = noe.posicion[1];
		noe.primero->direccion = noe.direccion;
	}

}