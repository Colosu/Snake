#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "Objetos.h"
#include "Mapa.h"
#include "Movimiento.h"
#include "Presentacion.h"

int main() {

	tMapa mapa;
	tSerpiente serpiente;

	//idioma();
	srand(time(NULL));
	limpiar();

	inicializarSerpiente(serpiente);
	mapa = inicializarMapa(serpiente);
	mostrarMapa(mapa, cout);

	while (serpiente.contador > 0) {

		mover(mapa, serpiente, cin);
		limpiar();
		mostrarMapa(mapa, cout);
	}

	eliminarMapa(mapa);

	return 0;
}