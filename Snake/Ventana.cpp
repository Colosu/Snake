#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_ttf.h"
#include "Ventana.h"

void logSDLError(const string &mensaje, ostream &oflujo = cerr) {

	oflujo << mensaje << " error: " << SDL_GetError() << endl;
}

int inicializarSDL(Uint32 subsistemas) {

	int inicializado = 0;

	if (SDL_Init(subsistemas) < 0) {

		logSDLError("SDL_Init()", cerr);
		inicializado = 1;
	}
	return inicializado;
}

int inicializarSDL_Image(IMG_InitFlags subsistemas) {

	int inicializado = 0;

	if ((IMG_Init(subsistemas) & subsistemas) != subsistemas) {

		logSDLError("IMG_Init()", cerr);
		inicializado = 2;
	}

	return inicializado;
}

int inicializarSDL_ttf() {

	int inicializado = 0;

	if (TTF_Init() != 0) {

		logSDLError("TTF_Init()", cerr);
		inicializado = 3;
	}

	return inicializado;
}

int inicializarVentana(SDL_Window *&ventana, SDL_Renderer *&renderizado, string nombre) {

	int inicializado = 0;

	ventana = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, VENTANA_X, (VENTANA_Y + VENTANA_EXTRA), SDL_WINDOW_SHOWN);
	if (ventana == NULL) {

		logSDLError("SDL_CreateWindow()", cerr);
		inicializado = 4;
	} else {

		renderizado = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderizado == NULL) {

			logSDLError("SDL_CreateRenderer()", cerr);
			inicializado = 5;
		} else {

			SDL_SetRenderDrawColor(renderizado, 0x00, 0x0, 0x00, 0xFF);
		}
	}
	return inicializado;
}

int inicializarFuente(TTF_Font *&fuente, const string &archivo, int tamaño) {

	int inicializado = 0;

	fuente = TTF_OpenFont(archivo.c_str(), tamaño);

	if (fuente == NULL) {

		logSDLError("TTF_OpenFont()", cerr);
		inicializado = 6;
	}
	return inicializado;
}

SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado) {

	SDL_Texture *textura = NULL;
	textura = IMG_LoadTexture(renderizado, archivo.c_str());
	if (textura == NULL) {
		logSDLError("IMG_LoadTexture()", cerr);
	}

	return textura;
}

void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y, SDL_Rect *clip) {

	SDL_Rect rectangulo;

	rectangulo.x = x;
	rectangulo.y = y;

	if (clip != NULL) {

		rectangulo.w = clip -> w;
		rectangulo.h = clip -> h;
	} else {

		SDL_QueryTexture(textura, NULL, NULL, &rectangulo.w, &rectangulo.h);
	}

	renderizarTextura(textura, renderizado, rectangulo, clip);
}

void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, SDL_Rect rectangulo, SDL_Rect *clip) {

	SDL_RenderCopy(renderizado, textura, clip, &rectangulo);
}

SDL_Texture* renderizarTexto(TTF_Font *fuente, const string &mensaje, SDL_Color color, SDL_Renderer *renderizado) {

	SDL_Texture *textura = NULL;

	SDL_Surface *superficie = NULL;
	superficie = TTF_RenderText_Blended(fuente, mensaje.c_str(), color);

	if (superficie == NULL) {

		logSDLError("TTF_RenderText_Blended()", cerr);
	} else {

		textura = SDL_CreateTextureFromSurface(renderizado, superficie);

		if (textura == NULL) {

			logSDLError("SDL_CreateTextureFromSurface", cerr);
		}

		SDL_FreeSurface(superficie);
	}

	return textura;
}