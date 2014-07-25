#ifndef VENTANA_H
#define VENTANA_H

#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL_image.h"

const int VENTANA_X = 600;
const int VENTANA_Y = 600;
const int TAMANO_CASILLA = 15;

void logSDLError(const string &mensaje, ostream &oflujo);
int inicializarSDL(Uint32 subsistemas);
int inicializarSDL_Image(IMG_InitFlags subsistemas);
int inicializarVentana(SDL_Window *&ventana, SDL_Renderer *&renderizado, string nombre);
SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado);
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y);
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y, int ancho, int alto);

#endif