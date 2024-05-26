#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"

using namespace std;

class Tetris
{
public:
	Tetris();

	void juga(double const deltaTime); //PROVISIONAL
	//void mostraPuntuacions(); //PROVISIONAL
	void inicialitza(string const fitxerInicial, string const fitxerFigures, string const fitxerMov);

	bool menuInicial(string const fitxerPuntuacions);
	int getMode() const { return m_mode; }
	bool finalPartida(string const fitxerPuntuacions);


	//void menuInicial();

private:
	Partida m_partida;
	int m_mode;
};

//void menuInicial(int& mode); //PROVISIONAL

#endif;
