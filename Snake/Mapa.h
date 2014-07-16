#ifndef MAPA_H
#define MAPA_H

#include <Windows.h>
#include "Serpiente.h"

const int FILAS = 39;
const int COLUMNAS = 39;

typedef enum { // Screen colors
	black,         //  0
	dark_blue,     //  1
	dark_green,    //  2
	dark_cyan,     //  3
	dark_red,      //  4
	dark_magenta,  //  5
	dark_yellow,   //  6
	light_gray,    //  7
	dark_gray,     //  8
	light_blue,    //  9
	light_green,   // 10
	light_cyan,    // 11
	light_red,     // 12
	light_magenta, // 13
	light_yellow,  // 14
	white          // 15
} tColor;

typedef struct {

	int tipo;
} tCasilla;

typedef struct {

	tCasilla mapa[FILAS][COLUMNAS];
} tMapa;

tMapa* inicializarMapa();
void eliminarMapa(tMapa *mapa);
void mostrarMapa(tMapa *mapa, ostream &oflujo);
void actualizarMapa(tMapa *mapa, tSerpiente serpiente, int fila, int columna);

void setColor(tColor color); //Cambia el color de la consola.



#endif