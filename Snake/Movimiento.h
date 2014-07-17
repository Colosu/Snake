#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <iostream>
using namespace std;
#include "Mapa.h"
#include "Objetos.h"
#include "Presentacion.h"

void mover(tMapa &mapa, tSerpiente &serpiente, istream &iflujo);
void generarManzana(int &tipo, int &fila, int &columna);

#endif