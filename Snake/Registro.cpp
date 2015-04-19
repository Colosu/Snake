#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Registro.h"
#include "Objetos.h"
#include "Ventana.h"

void ranking(const tNoe &noe) {

	string jugador = "colosu", archivo = "rankings.txt";
	bool actualizado;

	//cout << "Introduzca su nombre de jugador: ";
	//cin >> jugador;

	actualizado = actualizarRanking(jugador, archivo, noe.puntuacion);

	if (!actualizado) {

		//cout << "no se ha podido actualizar el ranking" << endl;
	} else {

		//mostrarRanking();
	}
}

bool actualizarRanking(string jugador, string archivo, int puntos) {

	ifstream leer;
	ofstream escribir;
	string nombre, backup = "rankingsBackup.txt";
	int puntuacion = 0, juegos = 0;
	bool resultado = true, actualizado = false, copiado = false;

	leer.open(archivo);
	if (!leer.is_open()) {

		escribir.open(archivo);
		escribir << left << setw(20) << "Jugador" << setw(15) << "Partidas" << "Puntos";
		escribir << endl << "XXX";
		escribir.close();
	} else {
		leer.close();
	}

	copiado = copiarArchivo(archivo, backup);

	if (copiado) {

		escribir.open(archivo);
		leer.open(backup);

		if (!escribir.is_open() || !leer.is_open()) {

			resultado = false;
		} else {

			leer >> nombre;
			escribir << nombre;
			getline(leer, nombre);
			escribir << nombre;

			while (nombre != "XXX") {

				leer >> nombre;

				if (jugador == nombre) {

					leer >> juegos >> puntuacion;
					escribir << endl << left << setw(23) << jugador << setw(15) << juegos + 1;
					escribir << puntuacion + puntos;
					actualizado = true;

				} else if (nombre == "XXX" && actualizado == false) {

					escribir << endl << left << setw(23) << jugador << setw(15) << 1;
					escribir << puntos;
					escribir << endl << nombre;
				} else if (nombre == "XXX") {

					escribir << endl << nombre;

				} else {

					escribir << endl << nombre;
					getline(leer, nombre);
					escribir << nombre;

				}
			}
		}

		leer.close();
		escribir.close();
	} else {

		resultado = false;
	}
	return resultado;
}

/*void mostrarRanking() {


}*/

bool copiarArchivo(string archivo, string auxiliar) {

	string line;
	ifstream original;
	ofstream copia;
	bool resultado;

	original.open(archivo);
	copia.open(auxiliar);

	if (!original.is_open() || !copia.is_open()) {

		resultado = false;

	} else {

		getline(original, line);
		copia << line;

		while (original.good()) {

			getline(original, line);
			copia << endl << line;

		}

		original.close();
		copia.close();

		resultado = true;
	}

	return resultado;
}