#ifndef VENTANA_H
#define VENTANA_H

#include <iostream>
#include <string>
using namespace std;

const int VENTANA_X = 640;
const int VENTANA_Y = 480;

bool inicializarSDL(SDL_Window *ventana, SDL_Renderer *renderizado);
void logSDLError(const string mensaje, ostream &oflujo = cout);

#endif