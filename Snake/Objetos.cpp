#include "include\SDL2\SDL.h"
#include "Objetos.h"

void inicializarNoe(tNoe &noe, SDL_Rect clipsNoe[4]) {

	noe.tipo = 0;
	noe.posicion[0] = 1;
	noe.posicion[1] = 1;
	noe.direccion = tDireccion(0);
	noe.contador = 1;
	noe.puntuacion = 0;
	noe.primero = NULL;

	for (int i = 0; i < 4; i++) {

		clipsNoe[i].x = (i % 4) * CASILLA_ANCHO;
		clipsNoe[i].y = (i / 4) * CASILLA_ALTO;
		clipsNoe[i].w = CASILLA_ANCHO;
		clipsNoe[i].h = CASILLA_ALTO;
	}
}

void agregarAnimal(tNoe &noe, const tAnimal &animal) {

	tCadena ultimo = noe.primero;

	if (noe.contador > 1) {

		for (int i = 0; i < (noe.contador - 2); i++) {

			ultimo = ultimo->siguiente;
		}

		ultimo->siguiente = new tAnimal;
		ultimo->siguiente->animal = animal.animal;
		ultimo->siguiente->alimentacion = animal.alimentacion;
		ultimo->siguiente->posicion[0] = animal.posicion[0];
		ultimo->siguiente->posicion[1] = animal.posicion[1];
		ultimo->siguiente->direccion = animal.direccion;
		ultimo->siguiente->siguiente = animal.siguiente;
	} else {

		noe.primero = new tAnimal;
		noe.primero->animal = animal.animal;
		noe.primero->alimentacion = animal.alimentacion;
		noe.primero->posicion[0] = animal.posicion[0];
		noe.primero->posicion[1] = animal.posicion[1];
		noe.primero->direccion = animal.direccion;
		noe.primero->siguiente = animal.siguiente;
	}

}

void actualizarCadena(tNoe &noe) {

	int I = 1;
	tCadena anterior, posterior;

	while (I < (noe.contador - 2)) {

		anterior = noe.primero;
		posterior = noe.primero;

		for (int i = 0; i < (I); i++) {

			anterior = anterior->siguiente;
		}

		for (int i = 0; i < (I - 1); i++) {

			posterior = posterior->siguiente;
		}

		if (anterior->alimentacion == (posterior->alimentacion + 1) && I == 1) {

			anterior->posicion[0] = posterior->posicion[0];
			anterior->posicion[1] = posterior->posicion[1];
			anterior->direccion = posterior->direccion;
			delete noe.primero;
			noe.primero = anterior;
			noe.contador--;
			I--;
		} else if (anterior->alimentacion == (posterior->alimentacion + 1)) {

			tCadena tmp;

			tmp = noe.primero;

			for (int i = 0; i < (I - 2); i++) {

				tmp = tmp->siguiente;
			}

			anterior->posicion[0] = posterior->posicion[0];
			anterior->posicion[1] = posterior->posicion[1];
			anterior->direccion = posterior->direccion;
			delete tmp->siguiente;
			tmp->siguiente = anterior;
			noe.contador--;
			I--;
		}

		I++;
	}
}