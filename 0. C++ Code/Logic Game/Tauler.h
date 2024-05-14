#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;


class Tauler
{
public:
	Tauler();

	void setCasella(int fila, int columna, int valor);
	int getCasella(int fila, int columna);


	bool comprovaSiCasellaForaTauler(int const fila, int const columna); //no necesaria?

	void actualitzaTauler(Figura figura);//posar la figura al tauler despres de comprovar que l'accio es pot fer
	void guardaTauler(string nomFitxer);

	int eliminarFila(int fila, int columna); // elimina fila sencera

private:
	int m_tauler[MAX_FILA][MAX_COL];
};
#endif
