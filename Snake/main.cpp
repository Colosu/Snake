#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_ttf.h"
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
	TTF_Font *fuentePrincipal = NULL;
	TTF_Font *fuenteJuego = NULL;
	SDL_Texture *agujeros = NULL;
	SDL_Texture *manzanas = NULL;
	SDL_Texture *serpiente1 = NULL;
	//SDL_Texture *serpiente2 = NULL;
	SDL_Texture *inicio = NULL;
	SDL_Texture *iniciar = NULL;
	SDL_Texture *titulo = NULL;
	SDL_Texture *puntuacion = NULL;
	SDL_Rect clipsSerpiente[12];
	SDL_Event evento;
	string direccion;
	int inicializado = 0;
	bool empezar, finalizar;

	srand(time(NULL));

	direccion = obtenerDireccion("");

	inicializado = inicializarSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if (inicializado == 0) {

		inicializado = inicializarSDL_Image(IMG_INIT_PNG);

		if (inicializado == 0) {

			inicializado = inicializarSDL_ttf();

			if (inicializado == 0) {

				inicializado = inicializarVentana(ventana, renderizado, "Snake");

				if (inicializado == 0) {

					int inicializado1 = 0, inicializado2 = 0;

					inicializado1 = inicializarFuente(fuentePrincipal, direccion + "BirdsofParadise.ttf", 12);
					inicializado2 = inicializarFuente(fuenteJuego, direccion + "DigitalAnarchy.ttf", 12);
					inicializado = inicializado1 + inicializado2;

					if (inicializado == 0) {

						agujeros = cargarTextura(direccion + "agujeros.bmp", renderizado);
						manzanas = cargarTextura(direccion + "manzanas.png", renderizado);
						serpiente1 = cargarTextura(direccion + "serpiente1.png", renderizado);
						//serpiente2 = cargarTextura(direccion + "serpiente2.bmp", renderizado);
						inicio = cargarTextura(direccion + "inicio.bmp", renderizado);

						if (agujeros != NULL && manzanas != NULL && serpiente1 != NULL /*&& serpiente2 != NULL*/ && inicio != NULL) {

							SDL_Color color1 = { 255, 255, 255, 255 };
							SDL_Color color2 = { 0, 0, 0, 255 };

							iniciar = renderizarTexto(fuentePrincipal, "Iniciar", color1, renderizado);
							titulo = renderizarTexto(fuentePrincipal, "Snake", color1, renderizado);
							puntuacion = renderizarTexto(fuenteJuego, "Puntuación", color2, renderizado);

							if (iniciar != NULL && titulo != NULL && puntuacion != NULL) {

								int ancho, alto;
								empezar = false;
								finalizar = false;

								while (!empezar && !finalizar) {

									mostrarInicio(renderizado, inicio, iniciar, titulo);

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
								inicializarSerpiente(serpiente, clipsSerpiente);
								SDL_SetRenderDrawColor(renderizado, 0xEF, 0xED, 0xB9, 0xFF);
								mapa = inicializarMapa(serpiente);
								mostrarMapa(mapa, serpiente, renderizado, agujeros, manzanas, serpiente1, clipsSerpiente);

								while (!finalizar) {

									while (SDL_PollEvent(&evento)) {

										if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
											finalizar = true;
										}
										if (evento.type == SDL_KEYDOWN) {  //Presiona una tecla

											mover(mapa, serpiente, evento);
										}
									}

									mostrarMapa(mapa, serpiente, renderizado, agujeros, manzanas, serpiente1, clipsSerpiente);
									if (serpiente.contador <= 0) {

										finalizar = true;
									}
								}

								eliminarMapa(mapa);

								SDL_DestroyTexture(iniciar);
								SDL_DestroyTexture(titulo);
								SDL_DestroyTexture(puntuacion);
							}

							SDL_DestroyTexture(agujeros);
							SDL_DestroyTexture(manzanas);
							SDL_DestroyTexture(serpiente1);
							//SDL_DestroyTexture(serpiente2);
						}

						TTF_CloseFont(fuentePrincipal);
						TTF_CloseFont(fuenteJuego);
					}

					SDL_DestroyRenderer(renderizado);

					SDL_DestroyWindow(ventana);
				} else if (inicializado == 5) {

					SDL_DestroyWindow(ventana);
				}

				TTF_Quit();
			}

			IMG_Quit();
		}

		SDL_Quit();
	}
	SDL_Delay(5000);
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