#include <iostream>
using namespace std;
#include <Windows.h>
#include "Mapa.h"

void mostrarCasilla(tCasilla casilla, ostream &oflujo);

tMapa* inicializarMapa() {

	tMapa *mapa = new tMapa;

	//Se inicializan todas las casillas.
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			mapa->mapa[i][j].tipo = 0;
		}
	}

	//Se crean los bordes.
	for (int i = 0; i < COLUMNAS; i++) {

		mapa->mapa[0][i].tipo = -1;
		mapa->mapa[FILAS - 1][i].tipo = -1;
	}
	for (int i = 1; i < FILAS - 1; i++) {

		mapa->mapa[i][0].tipo = -1;
		mapa->mapa[i][COLUMNAS - 1].tipo = -1;
	}

	//Se coloca la serpiente
	mapa->mapa[3][3].tipo = 1;

	//Se coloca la primera manzana
	mapa->mapa[7][7].tipo = -2;

	return mapa;
}

void mostrarMapa(const tMapa &mapa, ostream &oflujo = cout) {

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {

			mostrarCasilla(mapa.mapa[i][j], oflujo);
		}
		oflujo << endl;
	}

}

void mostrarCasilla(tCasilla casilla, ostream &oflujo = cout) {

	if (casilla.tipo == -1) {

		setColor(dark_blue);
		oflujo << char(219) << char(219);
		setColor(white);
	} else if (casilla.tipo == -2) {

		setColor(dark_red);
		oflujo << char(219) << char(219);
		setColor(white);
	} else if (casilla.tipo > 0) {

		setColor(light_green);
		oflujo << char(219) << char(219);
		setColor(white);
	} else {

		oflujo << "  ";
	}
}


void setColor(tColor color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}