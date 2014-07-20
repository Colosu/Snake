#include <cstdlib>
#include "include\SDL2\SDL.h"
#include "Mapa.h"
#include "Objetos.h"
#include "Ventana.h"
#include "Presentacion.h"

void mostrarCasilla(tCasilla casilla, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *bordes, SDL_Texture *manzanas, SDL_Texture *cabezaSerpiente, SDL_Texture *serpientes, int fila, int columna);

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

void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio) {

	int largo, alto;

	SDL_RenderClear(renderizado);
	
	SDL_QueryTexture(inicio, NULL, NULL, &largo, &alto);
	renderizarTextura(inicio, renderizado, (VENTANA_X / 2) - (largo / 2), (VENTANA_Y / 2) - (alto / 2));

	SDL_RenderPresent(renderizado);
}

void mostrarMapa(tMapa mapa, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *bordes, SDL_Texture *manzanas, SDL_Texture *cabezaSerpiente, SDL_Texture *serpientes) {

	SDL_RenderClear(renderizado);

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {

			mostrarCasilla(mapa.mapa[i][j], serpiente, renderizado, bordes, manzanas, cabezaSerpiente, serpientes, i, j);
		}
	}

	SDL_RenderPresent(renderizado);
}

void mostrarCasilla(tCasilla casilla, tSerpiente serpiente, SDL_Renderer *renderizado, SDL_Texture *bordes, SDL_Texture *manzanas, SDL_Texture *cabezaSerpiente, SDL_Texture *serpientes, int fila, int columna) {

	int largo, alto;

	if (casilla.tipo == -1) {

		SDL_QueryTexture(bordes, NULL, NULL, &largo, &alto);
		renderizarTextura(bordes, renderizado, columna*largo, fila*alto);
	} else if (casilla.tipo == -2) {

		SDL_QueryTexture(manzanas, NULL, NULL, &largo, &alto);
		renderizarTextura(manzanas, renderizado, columna*largo, fila*alto);
	} else if (casilla.tipo != 0 && casilla.tipo == serpiente.contador) {

		SDL_QueryTexture(cabezaSerpiente, NULL, NULL, &largo, &alto);
		renderizarTextura(cabezaSerpiente, renderizado, columna*largo, fila*alto);
	} else if (casilla.tipo > 0) {

		SDL_QueryTexture(serpientes, NULL, NULL, &largo, &alto);
		renderizarTextura(serpientes, renderizado, columna*largo, fila*alto);
	}
}

void actualizarMapa(tMapa &mapa, tSerpiente &serpiente, int fila, int columna) {

	if (mapa.mapa[fila][columna].tipo == -2) {

		serpiente.contador++;
		mapa.mapa[fila][columna].tipo = serpiente.contador;
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
}

void generarManzana(tMapa &mapa) {

	int fila, columna;

	fila = (rand() % (FILAS - 2)) + 1;
	columna = (rand() % (COLUMNAS - 2)) + 1;

	while (mapa.mapa[fila][columna].tipo > 0) {

		fila = (rand() % (FILAS - 2)) + 1;
		columna = (rand() % (COLUMNAS - 2)) + 1;
	}

	mapa.mapa[fila][columna].tipo = -2;
}