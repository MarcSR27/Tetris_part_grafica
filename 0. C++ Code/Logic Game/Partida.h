#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;


class Partida 
{
public:
    Partida();
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(double deltaTime);

    int generarNumAleatori(int min, int max);
    TipusFigura generarFiguraAleatoria(TipusFigura min, TipusFigura max);
    void dibuixaFigura(Figura& figura);
    void movimentFigura(Figura& figura);

private:
    double m_temps;
    static const int MIDA = 4;
    ColorFigura m_forma[MIDA][MIDA];
    int m_fila, m_columna;
    int m_puntuacio;
    Joc m_joc;
    bool m_figuraInicialGenerada = false;

    TipusFigura m_figuraNova;
    int m_estatFiguraNova;
    Figura m_figura;
};

#endif 
