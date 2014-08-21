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
	tNoe noe;
	tAnimal animal;
	SDL_Window *ventana = NULL;
	SDL_Renderer *renderizado = NULL;
	TTF_Font *fuentePrincipal = NULL;
	TTF_Font *fuenteSecundaria = NULL;
	TTF_Font *fuenteJuego = NULL;
	SDL_Texture *agua = NULL;
	SDL_Texture *manzanas = NULL;
	SDL_Texture *noes = NULL;
	SDL_Texture *animales[3];
	SDL_Texture *titulo = NULL;
	SDL_Texture *inicio = NULL;
	SDL_Texture *iniciar = NULL;
	SDL_Texture *puntuacion = NULL;
	SDL_Texture *puntos = NULL;
	SDL_Rect clipsNoe[4];
	SDL_Event evento;
	string direccion;
	string cadenaPuntos = "0";
	int inicializado = 0;
	bool empezar, finalizar;

	animales[0] = NULL;
	animales[1] = NULL;
	animales[2] = NULL;

	srand(time(NULL));

	direccion = obtenerDireccion("");

	inicializado = inicializarSDL(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if (inicializado == 0) {

		inicializado = inicializarSDL_Image(IMG_INIT_PNG);

		if (inicializado == 0) {

			inicializado = inicializarSDL_ttf();

			if (inicializado == 0) {

				inicializado = inicializarVentana(ventana, renderizado, "Noé");

				if (inicializado == 0) {

					int inicializado1 = 0, inicializado2 = 0, inicializado3 = 0;

					inicializado1 = inicializarFuente(fuentePrincipal, direccion + "BirdsofParadise.ttf", 100);
					inicializado2 = inicializarFuente(fuenteSecundaria, direccion + "BirdsofParadise.ttf", 50);
					inicializado3 = inicializarFuente(fuenteJuego, direccion + "Square.ttf", 20);
					inicializado = inicializado1 + inicializado2 + inicializado3;

					if (inicializado == 0) {

						agua = cargarTextura(direccion + "agua.bmp", renderizado);
						manzanas = cargarTextura(direccion + "manzanas.png", renderizado);
						noes = cargarTextura(direccion + "noe.png", renderizado);
						animales[0] = cargarTextura(direccion + "tipo1.bmp", renderizado);
						animales[1] = cargarTextura(direccion + "tipo2.bmp", renderizado);
						animales[2] = cargarTextura(direccion + "tipo3.bmp", renderizado);
						inicio = cargarTextura(direccion + "inicio.bmp", renderizado);

						if (agua != NULL && manzanas != NULL && noes != NULL && animales[0] != NULL && animales[1] != NULL && animales[2] != NULL && inicio != NULL) {

							SDL_Color color1 = { 255, 255, 255, 255 };
							SDL_Color color2 = { 0, 0, 0, 255 };

							titulo = renderizarTexto(fuentePrincipal, "Noé", color1, renderizado);
							iniciar = renderizarTexto(fuenteSecundaria, "Iniciar", color1, renderizado);
							puntuacion = renderizarTexto(fuenteJuego, "Puntuación: ", color2, renderizado);
							puntos = renderizarTexto(fuenteJuego, cadenaPuntos, color2, renderizado);

							if (iniciar != NULL && titulo != NULL && puntuacion != NULL && puntos != NULL) {

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
								inicializarNoe(noe, clipsNoe);
								SDL_SetRenderDrawColor(renderizado, 0xEF, 0xED, 0xB9, 0xFF);
								mapa = inicializarMapa(noe, animal);
								mostrarMapa(mapa, noe, animal, renderizado, puntuacion, puntos, agua, manzanas, noes, clipsNoe, animales);

								while (!finalizar) {

									while (SDL_PollEvent(&evento)) {

										if (evento.type == SDL_QUIT) { //Cierra la ventana con la X
											finalizar = true;
										}
										if (evento.type == SDL_KEYDOWN) {  //Presiona una tecla

											mover(mapa, noe, animal, evento);
										}
									}

									SDL_DestroyTexture(puntos);

									int tmp = noe.puntuacion;

									if (tmp != 0) {

										cadenaPuntos = "";

										while (tmp != 0) {

											cadenaPuntos = char((tmp % 10) + 48) + cadenaPuntos;
											tmp /= 10;
										}
									}

									puntos = renderizarTexto(fuenteJuego, cadenaPuntos, color2, renderizado);
									mostrarMapa(mapa, noe, animal, renderizado, puntuacion, puntos, agua, manzanas, noes, clipsNoe, animales);
									if (noe.contador <= 0) {

										finalizar = true;
									}
								}

								eliminarMapa(mapa);

								SDL_DestroyTexture(titulo);
								SDL_DestroyTexture(iniciar);
								SDL_DestroyTexture(puntuacion);
								SDL_DestroyTexture(puntos);
							}

							SDL_DestroyTexture(agua);
							SDL_DestroyTexture(manzanas);
							SDL_DestroyTexture(noes);
							SDL_DestroyTexture(animales[0]);
							SDL_DestroyTexture(animales[1]);
							SDL_DestroyTexture(animales[2]);
						}

						TTF_CloseFont(fuentePrincipal);
						TTF_CloseFont(fuenteSecundaria);
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