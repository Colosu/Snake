#ifndef VENTANA_H
#define VENTANA_H

#include <iostream>
#include <string>
using namespace std;
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_ttf.h"

const int VENTANA_X = 400; //Ancho de la ventana.
const int VENTANA_Y = 400; //Alto de la ventana.
const int VENTANA_EXTRA_X = 0; //Añadido al ancho de la ventana para colocar un posible HUD.
const int VENTANA_EXTRA_Y = 55; //Añadido al alto de la ventana para colocar un posible HUD.

void logSDLError(const string &mensaje, ostream &oflujo); //Muestra por el flujo "oflujo" el error "mensaje" producido.
int inicializarSDL(Uint32 subsistemas); //Inicializa SDL con los subsistemas "subsistemas".
int inicializarSDL_Image(IMG_InitFlags subsistemas); //Inicia el subsistema de Imagen con los subsistemas "subsistemas".
int inicializarSDL_ttf(); //Inicializa el subsistema de texto.
int inicializarVentana(SDL_Window *&ventana, SDL_Renderer *&renderizado, string nombre); //Inicializa la ventana del programa y su capa de renderizado con el nombre "nombre".
int inicializarFuente(TTF_Font *&fuente, const string &archivo, int tamaño); //Carga la fuente de texto "fuente" del archivo "archivo" al tamaño "tamaño" para poder usarla.
SDL_Texture* cargarTextura(const string &archivo, SDL_Renderer *renderizado); //Carga una textura gráfica del archivo "archivo" para poder usarla.
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, int x, int y, SDL_Rect *clip = NULL); //Renderiza la textura "textura" para mostrarla por pantalla en la posición ("x", "y"). Con "clip" seleccionas una parte de la textura.
void renderizarTextura(SDL_Texture *textura, SDL_Renderer *renderizado, SDL_Rect rectangulo, SDL_Rect *clip = NULL); //Renderiza la textura "textura" para mostrarla por pantalla dentro del rectángulo "rectangulo". Con "clip" seleccionas una parte de la textura.
SDL_Texture* renderizarTexto(TTF_Font *fuente, const string &mensaje, SDL_Color color, SDL_Renderer *renderizado); //Crea una textura con el texto "mensaje" y con la fuente "fuente" y el color "color".

#endif