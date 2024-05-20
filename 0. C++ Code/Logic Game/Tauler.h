#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = N_FILES_TAULER;
const int MAX_COL = N_COL_TAULER;


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

	//segona Part
	void dibuixaTauler();

private:
	int m_tauler[MAX_FILA][MAX_COL];
};
#endif
