#pragma once
#pragma once
#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
#include <list>
using namespace std;

class Joc
{
public:
	Joc();
	void inicialitza(const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
	void escriuTauler(const string& nomFitxer);

	bool giraFigura(DireccioGir sentit);
	bool mouFigura(int dirX); //dirX == -1 per esquerre, dirX == 1 per dreta
	bool baixaFigura(int& filesEliminades);

	//segona part
	//Figura getFigura() { return m_figuraCaient; }
	bool setFigura(int const columna, TipusFigura const tipus, int const estat);
	void dibuixa(); //dibuixa el tauler i la figura
	int getFilaFigura() { return m_figuraCaient.getPosicioY(); }
	int getColFigura() { return m_figuraCaient.getPosicioX(); }

	void modeTest(); // No acabada

private:
	Figura m_figuraCaient;
	Tauler m_taulerJoc;

	int m_puntuacio;
	int m_nivell;

	void escriuFiguraAlTauler();
	void esborraFiguraDelTauler();
	bool comprovaMoviment(Figura& figuraSeguent); //comprova si la figura a posar colusiona amb una altra o sobrepassa els limits del tauler 

	list<Figura> m_figuraTest;
};



#endif