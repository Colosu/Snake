#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include "Objetos.h"

void ranking(const tNoe &noe); //Administra el registro de jugadores.
bool actualizarRanking(string jugador, string archivo, int puntos); //Actualiza el ranking.
//void mostrarRanking(); //Muestra el rankig de puntuaciones
bool copiarArchivo(string archivo, string auxiliar); //Copia el archivo en un archivo auxiliar.

#endif