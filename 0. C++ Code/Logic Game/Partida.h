#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

#include <random> // llibreria per num aleatoris
#include <string>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

typedef struct
{
    string nom;
    int puntuacio;
}Jugador;

class Partida
{
public:
    Partida();
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(int const mode, double deltaTime);

    ////
    int generarNumAleatori(int min, int max); //per generar columna i estat aleatori
    TipusFigura generarTipusFiguraAleatoria(/*TipusFigura min, TipusFigura max*/); //genera tipus de figura de forma aleatoria
    //void dibuixaFigura(Figura& figura);
    //void movimentFigura(Figura& figura);
    void figuraAleatoria(); //genera la figura aleatoria
    void puntuacioINivell(int const filesEliminades);

    void escriuPuntuacio(const string& nomFitxer);
    void mostraPuntuacio(const string& nomFitxer);

    int const getPuntuacio() { return m_puntuacio; }
    string getNomJugador() { return m_nomJugador; }

private:
    double m_temps;

    ////////
    Joc m_joc;
    int m_nivell;
    float m_incrementVelocitat; // per fer que augmenti la velocitat de caiguda de figuras
    int m_puntuacio; //revisar si cal (ja esta en joc)
    TipusTecla* m_moviment;
    bool m_partidaAcabada; //provisional
    //falta atribut per guardar les figures que cauran
    //int m_mode;
    string m_nomJugador; // provisional, ya es veura si es necesaria
};

#endif 
