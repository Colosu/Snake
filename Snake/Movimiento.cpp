#include <iostream>
using namespace std;
#include "Mapa.h"
#include "Objetos.h"
#include "Presentacion.h"

void mover(tMapa &mapa, tSerpiente &serpiente, istream &iflujo = cin) {

	char direccion;

	iflujo >> direccion;

	if (direccion == 'a' || direccion == 'A') {

		serpiente.columna--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (direccion == 'w' || direccion == 'W') {

		serpiente.fila--;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (direccion == 'd' || direccion == 'D') {

		serpiente.columna++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else if (direccion == 's' || direccion == 'S') {

		serpiente.fila++;
		actualizarMapa(mapa, serpiente, serpiente.fila, serpiente.columna);
	} else {

		iflujo.clear();
		iflujo.ignore();
	}

}