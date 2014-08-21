#ifndef OBJETOS_H
#define OBJETOS_H

const int CASILLA_ANCHO = 20;
const int CASILLA_ALTO = 20;
const int ANIMALES = 3;
const int ALIMENTACION = 3;

typedef enum {Norte, Sur, Este, Oeste} tDireccion;

struct tAnimal;

typedef tAnimal *tCadena;

struct tAnimal {
	int animal;
	int alimentacion;
	int posicion[2];
	tDireccion direccion;
	tCadena siguiente;
};

typedef struct {

	int tipo;
	int posicion[2];
	tDireccion direccion;
	int contador;
	int puntuacion;
	tCadena primero;
} tNoe;

void inicializarNoe(tNoe &noe, SDL_Rect clipsNoe[4]);
void agregarAnimal(tNoe &noe, const tAnimal &animal);
void actualizarCadena(tNoe &noe);

#endif