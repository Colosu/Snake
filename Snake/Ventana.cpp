#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL.h"
#include "Ventana.h"

void logSDLError(const string &mensaje, ostream &oflujo = cerr) {

	oflujo << mensaje << "error: " << SDL_GetError() << endl;
}

bool inicializarSDL(SDL_Window *ventana, SDL_Renderer *renderizado) {

	bool inicializado = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {

		logSDLError("SDL_Init()", cerr);
		inicializado = false;
	} else {

		ventana = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VENTANA_X, VENTANA_Y, SDL_WINDOW_SHOWN);
		if (ventana == NULL) {

			logSDLError("SDL_CreateWindow()", cerr);
			inicializado = false;
		} else {

			renderizado = SDL_CreateRenderer(ventana, -1, 0);
			if (renderizado == NULL) {

				logSDLError("SDL_CreateRenderer()", cerr);
				inicializado = false;
			}
		}
	}
	return inicializado;
}

SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado) {

	SDL_Texture *textura = NULL;
	SDL_Surface *imagenCargada = SDL_LoadBMP(archivo.c_str());

	if (imagenCargada != NULL){
		textura = SDL_CreateTextureFromSurface(renderizado, imagenCargada);
		SDL_FreeSurface(imagenCargada);

		if (textura == NULL) {
			logSDLError("Crear Textura Desde Superficie", cerr);
		}	
	} else {

		logSDLError("SDL_LoadBMP", cerr);
	}
		

	return textura;
}

void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y) {

	SDL_Rect rectangulo;

	rectangulo.x = x;
	rectangulo.y = y;

	SDL_QueryTexture(textura, NULL, NULL, &rectangulo.x, &rectangulo.y);
	SDL_RenderCopy(renderizado, textura, NULL, &rectangulo);
}
