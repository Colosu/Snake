#include <cstdlib>
#include "include\SDL2\SDL.h"
#include "Mapa.h"
#include "Objetos.h"
#include "Ventana.h"
#include "Presentacion.h"

void mostrarCasilla(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *agujeros, SDL_Texture *manzanas, SDL_Texture *serpientes, SDL_Rect clipsSerpiente[12], int fila, int columna);

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
			mapa.mapa[i][j].manzana = false;
			mapa.mapa[i][j].serpiente = false;
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
	mapa.mapa[serpiente.fila][serpiente.columna].serpiente = true;

	//Se coloca la primera manzana
	fila = (rand() % (FILAS - 2)) + 1;
	columna = (rand() % (COLUMNAS - 2)) + 1;

	while (fila == serpiente.fila && columna == serpiente.columna) {

		fila = (rand() % (FILAS - 2)) + 1;
		columna = (rand() % (COLUMNAS - 2)) + 1;
	}

	mapa.mapa[fila][columna].tipo = -2;
	mapa.mapa[fila][columna].manzana = true;

	return mapa;
}

void eliminarMapa(tMapa &mapa) {

	for (int i = 0; i < FILAS; i++) {

		delete[] mapa.mapa[i];
	}
	delete[] mapa.mapa;
}

void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio) {

	int largo, alto;

	SDL_RenderClear(renderizado);
	
	SDL_QueryTexture(inicio, NULL, NULL, &largo, &alto);
	renderizarTextura(inicio, renderizado, (VENTANA_X / 2) - (largo / 2), (VENTANA_Y / 2) - (alto / 2));

	SDL_RenderPresent(renderizado);
}

void mostrarMapa(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *agujeros, SDL_Texture *manzanas, SDL_Texture *serpientes, SDL_Rect clipsSerpiente[12]) {

	SDL_RenderClear(renderizado);

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {

			mostrarCasilla(mapa, serpiente, renderizado, agujeros, manzanas, serpientes, clipsSerpiente, i, j);
		}
	}

	SDL_RenderPresent(renderizado);
}

void mostrarCasilla(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *agujeros, SDL_Texture *manzanas, SDL_Texture *serpientes, SDL_Rect clipsSerpiente[12], int fila, int columna) {

	if (mapa.mapa[fila][columna].tipo == -1) {

		renderizarTextura(agujeros, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO);
	} else if (mapa.mapa[fila][columna].tipo == -2) {

		renderizarTextura(manzanas, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO);
	} else if (mapa.mapa[fila][columna].tipo != 0 && mapa.mapa[fila][columna].tipo == serpiente.contador) {

		renderizarTextura(serpientes, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO, &clipsSerpiente[serpiente.nuevaDireccion * 3]);
	} else if (mapa.mapa[fila][columna].tipo > 1) {

		renderizarTextura(serpientes, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO, &clipsSerpiente[1]);
	} else if (mapa.mapa[fila][columna].tipo == 1) {
		
		if (mapa.mapa[fila - 1][columna].tipo == 2) {

			serpiente.ultimaDireccion = tDireccion(0);
		} else if (mapa.mapa[fila + 1][columna].tipo == 2) {

			serpiente.ultimaDireccion = tDireccion(1);
		} else if (mapa.mapa[fila][columna + 1].tipo == 2) {

			serpiente.ultimaDireccion = tDireccion(2);
		} else if (mapa.mapa[fila][columna - 1].tipo == 2) {

			serpiente.ultimaDireccion = tDireccion(3);
		}

		if (mapa.mapa[fila][columna].manzana && mapa.mapa[fila][columna].serpiente) {

			renderizarTextura(agujeros, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO);
		}
		renderizarTextura(serpientes, renderizado, (columna - 1)*CASILLA_ANCHO, (fila - 1)*CASILLA_ALTO, &clipsSerpiente[(serpiente.ultimaDireccion * 3) + 2]);
	}
}

void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna) {

	if (mapa.mapa[fila][columna].tipo == -2) {

		serpiente.contador++;
		mapa.mapa[fila][columna].tipo = serpiente.contador;
		mapa.mapa[fila][columna].serpiente = true;
		generarManzana(mapa);
	} else if (mapa.mapa[fila][columna].tipo == -1) {

		serpiente.contador = 0;
	} else if (mapa.mapa[fila][columna].tipo > 0) {

		serpiente.contador = serpiente.contador - mapa.mapa[fila][columna].tipo + 1;
		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {

				if (mapa.mapa[i][j].tipo != mapa.mapa[fila][columna].tipo && mapa.mapa[i][j].tipo >= mapa.mapa[fila][columna].tipo) {

					mapa.mapa[i][j].tipo = mapa.mapa[i][j].tipo - mapa.mapa[fila][columna].tipo;
				} else if (mapa.mapa[i][j].tipo > 0 && mapa.mapa[i][j].tipo < mapa.mapa[fila][columna].tipo) {

					mapa.mapa[i][j].tipo = 0;
				}
			}
		}
		mapa.mapa[fila][columna].tipo = serpiente.contador;
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

	actualizarMapa(mapa);
}

void actualizarMapa(tMapa &mapa) {

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (mapa.mapa[i][j].manzana && mapa.mapa[i][j].serpiente && mapa.mapa[i][j].tipo <= 0) {

				mapa.mapa[i][j].tipo = -1;
			}
		}
	}
}

void generarManzana(tMapa &mapa) {

	int fila, columna;

	fila = (rand() % (FILAS - 2)) + 1;
	columna = (rand() % (COLUMNAS - 2)) + 1;

	while (mapa.mapa[fila][columna].tipo > 0 || mapa.mapa[fila][columna].manzana == true) {

		fila = (rand() % (FILAS - 2)) + 1;
		columna = (rand() % (COLUMNAS - 2)) + 1;
	}

	mapa.mapa[fila][columna].tipo = -2;
	mapa.mapa[fila][columna].manzana = true;
}