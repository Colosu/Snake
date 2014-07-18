#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "include\SDL2\SDL.h"
#include "Objetos.h"
#include "Mapa.h"
#include "Movimiento.h"
#include "Ventana.h"
#include "Presentacion.h"

string obtenerDireccion(const string &direccion);

int main(int argc, char **argv) {

	tMapa mapa;
	tSerpiente serpiente;
	SDL_Window *ventana = NULL;
	SDL_Renderer *renderizado = NULL;
	SDL_Texture *bordes = NULL;
	SDL_Texture *manzanas = NULL;
	SDL_Texture *serpientes = NULL;
	string direccion;
	int inicializado;

	//idioma();
	srand(time(NULL));
	limpiar();

	inicializado = inicializarSDL(ventana, renderizado);

	direccion = obtenerDireccion("");

	if (inicializado == 0) {

		bordes = cargarTextura(direccion + "bordes.bmp", renderizado);
		manzanas = cargarTextura(direccion + "manzanas.bmp", renderizado);
		serpientes = cargarTextura(direccion + "serpientes.bmp", renderizado);

		if (bordes == NULL && manzanas == NULL && serpientes == NULL) {

			inicializado = 4;
		} else if (bordes != NULL && manzanas == NULL && serpientes == NULL) {

			inicializado = 4;

			SDL_DestroyTexture(bordes);
		} else if (bordes == NULL && manzanas != NULL && serpientes == NULL) {

			inicializado = 4;

			SDL_DestroyTexture(manzanas);
		} else if (bordes == NULL && manzanas == NULL && serpientes != NULL) {

			inicializado = 4;

			SDL_DestroyTexture(serpientes);
		} else if (bordes != NULL && manzanas == NULL && serpientes != NULL) {

			inicializado = 4;

			SDL_DestroyTexture(bordes);
			SDL_DestroyTexture(serpientes);
		} else if (bordes == NULL && manzanas != NULL && serpientes != NULL) {

			inicializado = 4;

			SDL_DestroyTexture(manzanas);
			SDL_DestroyTexture(serpientes);
		} else if (bordes != NULL && manzanas != NULL && serpientes == NULL) {

			inicializado = 4;

			SDL_DestroyTexture(bordes);
			SDL_DestroyTexture(manzanas);
		} else {

			inicializarSerpiente(serpiente);
			mapa = inicializarMapa(serpiente);

			mostrarMapa(mapa, renderizado, bordes, manzanas, serpientes);

			while (serpiente.contador > 0) {

				mover(mapa, serpiente, cin);
				limpiar();
				mostrarMapa(mapa, renderizado, bordes, manzanas, serpientes);
			}

			eliminarMapa(mapa);
		}
	}

	if (inicializado == 4) {

		SDL_DestroyRenderer(renderizado);

		SDL_DestroyWindow(ventana);

		SDL_Quit();
	} else if (inicializado == 3) {

		SDL_DestroyWindow(ventana);

		SDL_Quit();
	} else if (inicializado == 2) {

		SDL_Quit();
	} else {

		SDL_DestroyTexture(bordes);
		SDL_DestroyTexture(manzanas);
		SDL_DestroyTexture(serpientes);

		SDL_DestroyRenderer(renderizado);

		SDL_DestroyWindow(ventana);

		SDL_Quit();
	}
	return 0;
}

string obtenerDireccion(const string &direccion = "") {

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

	static string baseRes;

	if (baseRes.empty()) {

		char *basePath = SDL_GetBasePath();
		if (basePath) {

			baseRes = basePath;
			SDL_free(basePath);
		} else {

			cerr << "Error obteniendo la ruta de datos: " << SDL_GetError() << endl;
			return "";
		}

		size_t pos = baseRes.find_last_of("bin") - 2;
		baseRes = baseRes.substr(0, pos) + "resources" + PATH_SEP;
	}

	return direccion.empty() ? baseRes : baseRes + direccion + PATH_SEP;
}