#include <iostream>
using namespace std;
#include <cstdlib>
#include "Presentacion.h"

void limpiar() {

	system("cls");
}

void pausa() {

	cout << endl << "  ";
	system("pause");
	limpiar();
}

void idioma() {

	cout << "  ";
	system("chcp 1252");
}