#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"

#include <string>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

class Tetris
{
public:
	Tetris();

	void juga(double const deltaTime);
	void inicialitza(string const fitxerInicial, string const fitxerFigures, string const fitxerMov);

	bool menuInicial(string const fitxerPuntuacions,string& partida, string& figures, string& moviments);
	int getMode() const { return m_mode; }
	bool finalPartida(string const fitxerPuntuacions);
	void imprimirMenu();

	void missatgeFinal();

	char controlResposta();
	bool menuMusica(int& opcio, string& musica);

private:
	Partida m_partida;
	int m_mode;
};

#endif;
