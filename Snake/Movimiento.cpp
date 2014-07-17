#include <iostream>
using namespace std;
#include "Mapa.h"
#include "Serpiente.h"
#include "Presentacion.h"

void mover(tMapa &mapa, tSerpiente &serpiente, istream &iflujo = cin) {

	char direccion;

	iflujo.get(direccion);

	if (direccion == 'a' || direccion == 'A') {

		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna - 1);
	} else if (direccion == 'w' || direccion == 'W') {

		actualizarMapa(mapa, serpiente, serpiente.fila - 1, serpiente.columna);
	} else if (direccion == 'd' || direccion == 'D') {

		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna + 1);
	} else if (direccion == 's' || direccion == 'S') {

		actualizarMapa(mapa, serpiente, serpiente.fila + 1, serpiente.columna);
	} else {

		iflujo.clear();
		iflujo.ignore();
	}

}