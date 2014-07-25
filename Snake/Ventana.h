#ifndef VENTANA_H
#define VENTANA_H

#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_ttf.h"

const int VENTANA_X = 600;
const int VENTANA_Y = 600;

void logSDLError(const string &mensaje, ostream &oflujo);
int inicializarSDL(Uint32 subsistemas);
int inicializarSDL_Image(IMG_InitFlags subsistemas);
int inicializarSDL_ttf();
int inicializarVentana(SDL_Window *&ventana, SDL_Renderer *&renderizado, string nombre);
int inicializarFuente(TTF_Font *&fuente, const string &archivo, int tamaño);
SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado);
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y, SDL_Rect *clip = NULL);
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, SDL_Rect rectangulo, SDL_Rect *clip = NULL);
SDL_Texture* renderizarTexto(TTF_Font *fuente, const string &mensaje, SDL_Color color, SDL_Renderer *renderizado);

#endif