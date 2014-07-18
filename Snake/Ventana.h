#ifndef VENTANA_H
#define VENTANA_H

#include <iostream>
#include <string>
using namespace std;

const int VENTANA_X = 600;
const int VENTANA_Y = 600;

void logSDLError(const string &mensaje, ostream &oflujo);
bool inicializarSDL(SDL_Window *ventana, SDL_Renderer *renderizado);
SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado);
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y);

#endif