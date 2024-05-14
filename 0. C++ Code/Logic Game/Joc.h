#pragma once
#pragma once
#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc();
	void inicialitza(const string& nomFitxer);
	void escriuTauler(const string& nomFitxer);

	bool giraFigura(DireccioGir sentit);
	bool mouFigura(int dirX); //dirX == -1 per esquerre, dirX == 1 per dreta
	int baixaFigura();


private:
	Figura m_figuraCaient;
	Tauler m_taulerJoc;

	int m_puntuacio;
	int m_nivell;

	void escriuFiguraAlTauler();
	void esborraFiguraDelTauler();
	bool comprovaMoviment(Figura& figuraSeguent); //comprova si la figura a posar colusiona amb una altra o sobrepassa els limits del tauler
};



#endif