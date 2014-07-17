#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL.h"
#include "Ventana.h"

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

void logSDLError(const string mensaje, ostream &oflujo = cout) {

	oflujo << mensaje << "error: " << SDL_GetError() << endl;
}
