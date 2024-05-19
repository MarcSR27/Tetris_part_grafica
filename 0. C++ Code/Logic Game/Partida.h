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

    ////
    int generarNumAleatori(int min, int max); //per generar columna i estat aleatori
    TipusFigura generarTipusFiguraAleatoria(/*TipusFigura min, TipusFigura max*/); //genera tipus de figura de forma aleatoria
    //void dibuixaFigura(Figura& figura);
    void movimentFigura(Figura& figura);
    void figuraAleatoria(); //genera la figura aleatoria

private:
    double m_temps;
    //esborrar
    static const int MIDA = 4;
    ColorFigura m_forma[MIDA][MIDA];
    int m_fila, m_columna;
    
    /////
    int m_puntuacio;
    Joc m_joc;
    bool m_figuraInicialGenerada = false; //esborra?

    TipusFigura m_figuraNova; //esborra?
    //int m_estatFiguraNova;
    int m_nivell;
};

#endif 
