#include <iostream>
using namespace std;
#include "Mapa.h"
#include "Presentacion.h"

int main() {

	tMapa *mapa;

	mapa = inicializarMapa();
	mostrarMapa(*mapa, cout);
	pausa();


	return 0;
}