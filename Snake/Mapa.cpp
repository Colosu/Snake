#include <cstdlib>
#include "include\SDL2\SDL.h"
#include "Mapa.h"
#include "Objetos.h"
#include "Ventana.h"
#include "Presentacion.h"

void mostrarCasilla(tMapa mapa, tNoe noe, tAnimal animal, SDL_Renderer *renderizado, SDL_Texture *agujeros, SDL_Texture *manzanas, SDL_Texture *noes, SDL_Rect clipsNoe[4], SDL_Texture *animales[3], int fila, int columna);

tMapa inicializarMapa(tNoe &noe, tAnimal &animal) {

	tMapa mapa;
	mapa.mapa = new tCasilla* [FILAS];
	for (int i = 0; i < FILAS; i++) {

		mapa.mapa[i] = new tCasilla [COLUMNAS];
	}

	//Se inicializan todas las casillas.
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			mapa.mapa[i][j].tipo = 0;
			mapa.mapa[i][j].animal = false;
			mapa.mapa[i][j].noe = false;
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

	//Se coloca a Noé
	noe.posicion[0] = (rand() % (FILAS - 2)) + 1;
	noe.posicion[1] = (rand() % (COLUMNAS - 2)) + 1;
	mapa.mapa[noe.posicion[0]][noe.posicion[1]].tipo = 1;
	mapa.mapa[noe.posicion[0]][noe.posicion[1]].noe = true;

	//Se coloca el primer animal
	generarAnimal(mapa, animal);

	return mapa;
}

void eliminarMapa(tMapa &mapa) {

	for (int i = 0; i < FILAS; i++) {

		delete[] mapa.mapa[i];
	}
	delete[] mapa.mapa;
}

void mostrarInicio(SDL_Renderer *renderizado, SDL_Texture *inicio, SDL_Texture *iniciar, SDL_Texture *titulo) {

	int largo, alto;

	SDL_RenderClear(renderizado);

	SDL_QueryTexture(titulo, NULL, NULL, &largo, &alto);
	renderizarTextura(titulo, renderizado, (VENTANA_X / 2) - (largo / 2), (VENTANA_Y / 5) - (alto / 2));
	SDL_QueryTexture(inicio, NULL, NULL, &largo, &alto);
	renderizarTextura(inicio, renderizado, (VENTANA_X / 2) - (largo / 2), (VENTANA_Y / 2) - (alto / 2));
	SDL_QueryTexture(iniciar, NULL, NULL, &largo, &alto);
	renderizarTextura(iniciar, renderizado, (VENTANA_X / 2) - (largo / 2), (VENTANA_Y / 2) - (alto / 2));

	SDL_RenderPresent(renderizado);
}

void mostrarMapa(tMapa mapa, tNoe noe, tAnimal animal, SDL_Renderer *renderizado, SDL_Texture *puntuacion, SDL_Texture *puntos, SDL_Texture *agua, SDL_Texture *manzanas, SDL_Texture *noes, SDL_Rect clipsNoe[4], SDL_Texture *animales[3]) {

	int largo1, largo2, alto;

	SDL_RenderClear(renderizado);

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {

			mostrarCasilla(mapa, noe, animal, renderizado, agua, manzanas, noes, clipsNoe, animales, i, j);
		}
	}

	SDL_QueryTexture(puntuacion, NULL, NULL, &largo1, &alto);
	renderizarTextura(puntuacion, renderizado, (VENTANA_X / 5) - (largo1 / 2), VENTANA_Y + 15 + ((VENTANA_EXTRA - 15) / 2) - (alto / 2));
	SDL_QueryTexture(puntos, NULL, NULL, &largo2, &alto);
	renderizarTextura(puntos, renderizado, (VENTANA_X / 5) + (largo1 / 2), VENTANA_Y + 15 + ((VENTANA_EXTRA - 15) / 2) - (alto / 2));

	SDL_RenderPresent(renderizado);
}

void mostrarCasilla(tMapa mapa, tNoe noe, tAnimal animal, SDL_Renderer *renderizado, SDL_Texture *agua, SDL_Texture *manzanas, SDL_Texture *noes, SDL_Rect clipsNoe[4], SDL_Texture *animales[3], int fila, int columna) {

	if (mapa.mapa[fila][columna].tipo == -1 && !(mapa.mapa[fila][columna].noe)) {

		renderizarTextura(agua, renderizado, columna * CASILLA_ANCHO, fila * CASILLA_ALTO);
	} else if (mapa.mapa[fila][columna].tipo == -2) {

		renderizarTextura(animales[((animal.alimentacion) - 1)], renderizado, columna * CASILLA_ANCHO, fila * CASILLA_ALTO);
	} else if (mapa.mapa[fila][columna].tipo == noe.contador && mapa.mapa[fila][columna].tipo > 0) {

		renderizarTextura(noes, renderizado, columna * CASILLA_ANCHO, fila * CASILLA_ALTO, &clipsNoe[int(noe.direccion)]);
	} else if (mapa.mapa[fila][columna].tipo > 0 && mapa.mapa[fila][columna].tipo < noe.contador) {
		
		tCadena anterior = noe.primero;

		for (int i = 0; i < (noe.contador - (mapa.mapa[fila][columna].tipo + 1)); i++) {

			anterior = anterior->siguiente;
		}

		if (mapa.mapa[fila][columna].animal && mapa.mapa[fila][columna].noe) {

			renderizarTextura(agua, renderizado, columna * CASILLA_ANCHO, fila * CASILLA_ALTO);
		}
		renderizarTextura(animales[((anterior->alimentacion) - 1)], renderizado, columna * CASILLA_ANCHO, fila * CASILLA_ALTO);
	}
}

void actualizarMapa(tMapa &mapa, tNoe &noe, tAnimal &animal, int fila, int columna) {

	actualizarCadena(noe);
	actualizarMapa(mapa, noe);

	if (mapa.mapa[fila][columna].tipo == -2) {

		agregarAnimal(noe, animal);
		noe.contador++;
		noe.puntuacion += 5;
		mapa.mapa[fila][columna].tipo = noe.contador;
		mapa.mapa[fila][columna].noe = true;
		generarAnimal(mapa, animal);
	} else if (mapa.mapa[fila][columna].tipo == -1) {

		noe.contador = 0;
	} else if (mapa.mapa[fila][columna].tipo > 0) {

		noe.contador -= (mapa.mapa[fila][columna].tipo - 1);
		noe.puntuacion -= (mapa.mapa[fila][columna].tipo * 3);
		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {

				if (mapa.mapa[i][j].tipo != mapa.mapa[fila][columna].tipo && mapa.mapa[i][j].tipo >= mapa.mapa[fila][columna].tipo) {

					mapa.mapa[i][j].tipo = mapa.mapa[i][j].tipo - mapa.mapa[fila][columna].tipo;
				} else if (mapa.mapa[i][j].tipo > 0 && mapa.mapa[i][j].tipo < mapa.mapa[fila][columna].tipo) {

					mapa.mapa[i][j].tipo = 0;
				}
			}
		}
		mapa.mapa[fila][columna].tipo = noe.contador;
		mapa.mapa[fila][columna].noe = true;
	} else {

		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {

				if (mapa.mapa[i][j].tipo > 0) {

					mapa.mapa[i][j].tipo--;
				}
			}
		}
		mapa.mapa[fila][columna].tipo = noe.contador;
		mapa.mapa[fila][columna].noe = true;
	}
}

void actualizarMapa(tMapa &mapa, tNoe &noe) {

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (mapa.mapa[i][j].animal && mapa.mapa[i][j].noe && mapa.mapa[i][j].tipo == 0) {

				mapa.mapa[i][j].tipo = -1;
				mapa.mapa[i][j].noe = false;
			}
			else if (mapa.mapa[i][j].noe && mapa.mapa[i][j].tipo == 0) {

				mapa.mapa[i][j].noe = false;
			}
		}
	}

	if (noe.contador < mapa.mapa[noe.posicion[0]][noe.posicion[1]].tipo) {

		for (int I = 0; I < (mapa.mapa[noe.posicion[0]][noe.posicion[1]].tipo - noe.contador); I++) {

			for (int i = 0; i < FILAS; i++) {
				for (int j = 0; j < COLUMNAS; j++) {

					if (mapa.mapa[i][j].tipo > 0) {

						mapa.mapa[i][j].tipo--;
					}
				}
			}
		}
	}
}

void generarAnimal(tMapa &mapa, tAnimal &animal) {

	int fila, columna;

	fila = (rand() % (FILAS - 2)) + 1;
	columna = (rand() % (COLUMNAS - 2)) + 1;

	while (mapa.mapa[fila][columna].tipo > 0 || mapa.mapa[fila][columna].animal == true) {

		fila = (rand() % (FILAS - 2)) + 1;
		columna = (rand() % (COLUMNAS - 2)) + 1;
	}

	mapa.mapa[fila][columna].tipo = -2;
	mapa.mapa[fila][columna].animal = true;
	animal.animal = (rand() % ANIMALES) + 1;
	animal.alimentacion = (rand() % ALIMENTACION) + 1;
	animal.direccion = Sur;
	animal.posicion[0] = fila;
	animal.posicion[1] = columna;
	animal.siguiente = NULL;
}