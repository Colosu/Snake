#include <iostream>
using namespace std;
#include <Windows.h>
#include "Mapa.h"
#include "Serpiente.h"
#include "Presentacion.h"

void mostrarCasilla(tCasilla casilla, ostream &oflujo);

tMapa inicializarMapa(tSerpiente &serpiente) {

	tMapa mapa;
	mapa.mapa = new tCasilla* [FILAS];
	for (int i = 0; i < FILAS; i++) {

		mapa.mapa[i] = new tCasilla [COLUMNAS];
	}

	int fila, columna;

	//Se inicializan todas las casillas.
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			mapa.mapa[i][j].tipo = 0;
		}
	}

	//Se crean los bordes.
	for (int i = 0; i < COLUMNAS; i++) {

		mapa.mapa[0][i].tipo = -1;
		mapa.mapa[FILAS - 1][i].tipo = -1;
	}
	for (int i = 1; i < FILAS - 1; i++) {

		mapa.mapa[i][0].tipo = -1;
		mapa.mapa[i][COLUMNAS - 1].tipo = -1;
	}

	//Se coloca la serpiente
	serpiente.fila = (rand() % (FILAS - 2)) + 1;
	serpiente.columna = (rand() % (COLUMNAS - 2)) + 1;
	mapa.mapa[serpiente.fila][serpiente.columna].tipo = serpiente.contador;

	//Se coloca la primera manzana
	fila = (rand() % (FILAS - 2)) + 1;
	columna = (rand() % (COLUMNAS - 2)) + 1;

	while (fila == serpiente.fila && columna == serpiente.columna) {

		fila = (rand() % (FILAS - 2)) + 1;
		columna = (rand() % (COLUMNAS - 2)) + 1;
	}

	mapa.mapa[fila][columna].tipo = -2;

	return mapa;
}

void eliminarMapa(tMapa &mapa) {

	for (int i = 0; i < FILAS; i++) {

		delete[] mapa.mapa[i];
	}
	delete[] mapa.mapa;
}

void mostrarMapa(tMapa mapa, ostream &oflujo = cout) {

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
	}
	else if (casilla.tipo == -2) {

		setColor(dark_red);
		oflujo << char(219) << char(219);
		setColor(white);
	}
	else if (casilla.tipo > 0) {

		setColor(light_green);
		oflujo << char(219) << char(219);
		setColor(white);
	}
	else {

		oflujo << "  ";
	}
}

void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna) {

	if (mapa.mapa[fila][columna].tipo == -2) {

		serpiente.contador++;
		mapa.mapa[fila][columna].tipo = serpiente.contador;
	} else if (mapa.mapa[fila][columna].tipo == -1) {

		serpiente.contador = 0;
	} else {

		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {

				if (mapa.mapa[i][j].tipo > 0) {

					mapa.mapa[i][j].tipo--;
				}
			}
		}
		mapa.mapa[fila][columna].tipo = serpiente.contador;
	}
}

void setColor(tColor color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}