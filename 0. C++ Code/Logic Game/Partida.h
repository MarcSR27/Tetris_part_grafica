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
    void inicialitza(int mode/*, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments*/);
    void actualitza(int const mode, double deltaTime);

    ////
    int generarNumAleatori(int min, int max); //per generar columna i estat aleatori
    TipusFigura generarTipusFiguraAleatoria(/*TipusFigura min, TipusFigura max*/); //genera tipus de figura de forma aleatoria
    //void dibuixaFigura(Figura& figura);
    //void movimentFigura(Figura& figura);
    void figuraAleatoria(); //genera la figura aleatoria
    void puntuacioINivell(int const filesEliminades);

private:
    double m_temps;

    ////////
    Joc m_joc;
    int m_nivell;
    int m_puntuacio; //revisar si cal (ja esta en joc)
    TipusTecla* m_moviment;
    bool m_partidaAcabada; //provisional
    //falta atribut per guardar les figures que cauran
};

#endif 
