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
    //void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(int const mode, double deltaTime);
    void inicialitza(int mode); //para provar el modo normal (no test)
    ////
    int generarNumAleatori(int min, int max); //per generar columna i estat aleatori
    TipusFigura generarTipusFiguraAleatoria(/*TipusFigura min, TipusFigura max*/); //genera tipus de figura de forma aleatoria
    //void dibuixaFigura(Figura& figura);
    //void movimentFigura(Figura& figura);
    void figuraAleatoria(); //genera la figura aleatoria

private:
    double m_temps;
    // Atributs necessaris només pels exemples d'utilització de la llibreria. 
    // S'hauran d'eliminar per la implementació del projecte
    /*static const int MIDA = 4;
    ColorFigura m_forma[MIDA][MIDA];
    int m_fila, m_columna;*/

    ////////
    Joc m_joc;
    int m_nivell;
    int m_puntuacio; //revisar si cal (ja esta en joc)
    TipusTecla* m_moviment;
    //falta atribut per guardar les figures que cauran
};

#endif 
