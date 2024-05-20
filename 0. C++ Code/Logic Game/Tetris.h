#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"

using namespace std;

class Tetris
{
public:
	Tetris() { m_partida = Partida(); }

	void juga(); //PROVISIONAL
	void mostraPuntuacions(); //PROVISIONAL
	void inicialitza();

	//void menuInicial(int& mode); //PROVISIONAL


private:
	Partida m_partida;
};

void menuInicial(int& mode); //PROVISIONAL

#endif;
