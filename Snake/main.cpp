#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"
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
	SDL_Texture *cabezaSerpiente = NULL;
	SDL_Texture *serpiente1 = NULL;
	//SDL_Texture *serpiente2 = NULL;
	SDL_Texture *inicio = NULL;
	SDL_Event evento;
	string direccion;
	int inicializado = 0;
	bool empezar, finalizar;

	srand(time(NULL));

	inicializado = inicializarSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if (inicializado == 0) {

		inicializado = inicializarSDL_Image(IMG_INIT_PNG);

		if (inicializado == 0) {

			inicializado = inicializarVentana(ventana, renderizado, "Snake");

			if (inicializado == 0) {

				direccion = obtenerDireccion("");

				bordes = cargarTextura(direccion + "bordes.bmp", renderizado);
				manzanas = cargarTextura(direccion + "manzanas.bmp", renderizado);
				cabezaSerpiente = cargarTextura(direccion + "cabezaSerpiente.bmp", renderizado);
				serpiente1 = cargarTextura(direccion + "serpiente1.bmp", renderizado);
				//serpiente2 = cargarTextura(direccion + "serpiente2.bmp", renderizado);
				inicio = cargarTextura(direccion + "inicio.bmp", renderizado);

				if (bordes != NULL && manzanas != NULL && cabezaSerpiente != NULL && serpiente1 != NULL /*&& serpiente2 != NULL*/ && inicio != NULL) {

					int ancho, alto;
					empezar = false;
					finalizar = false;

					while (!empezar && !finalizar) {

						mostrarInicio(renderizado, inicio);

						SDL_QueryTexture(inicio, NULL, NULL, &ancho, &alto);

						while (SDL_PollEvent(&evento)) {

							if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
								finalizar = true;
							}
							if (evento.type == SDL_KEYDOWN && (evento.key.keysym.sym == SDLK_KP_ENTER || evento.key.keysym.sym == SDLK_RETURN)) {  //Presiona el enter

								empezar = true;
							}
							if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && evento.button.x >= (VENTANA_X / 2) - (ancho / 2) && evento.button.x <= (VENTANA_X / 2) + (ancho / 2) && evento.button.y >= (VENTANA_Y / 2) - (alto / 2) && evento.button.y <= (VENTANA_Y / 2) + (alto / 2)) {  //Presiona el botón

								empezar = true;
							}
						}
					}
					inicializarSerpiente(serpiente);
					mapa = inicializarMapa(serpiente);
					mostrarMapa(mapa, serpiente, renderizado, bordes, manzanas, cabezaSerpiente, serpiente1);

					while (!finalizar) {

						while (SDL_PollEvent(&evento)) {

							if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
								finalizar = true;
							}
							if (evento.type == SDL_KEYDOWN) {  //Presiona una tecla

								mover(mapa, serpiente, evento);
							}
						}

						mostrarMapa(mapa, serpiente, renderizado, bordes, manzanas, cabezaSerpiente, serpiente1);
						if (serpiente.contador <= 0) {

							finalizar = true;
						}
					}

					eliminarMapa(mapa);

					SDL_DestroyTexture(bordes);
					SDL_DestroyTexture(manzanas);
					SDL_DestroyTexture(cabezaSerpiente);
					SDL_DestroyTexture(serpiente1);
					//SDL_DestroyTexture(serpiente2);
				}

				SDL_DestroyRenderer(renderizado);

				SDL_DestroyWindow(ventana);
			} else if (inicializado == 4) {

					SDL_DestroyWindow(ventana);
			}

			IMG_Quit();
		}

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