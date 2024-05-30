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

#include <Windows.h>
#include <mmsystem.h>

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
    TipusFigura generarTipusFiguraAleatoria(); //genera tipus de figura de forma aleatoria
    

    void figuraAleatoria(); //genera la figura aleatoria
    void puntuacioINivell(int const filesEliminades);

    void escriuPuntuacio(const string& nomFitxer);
    void mostraPuntuacio(const string& nomFitxer);

    void accionsTeclat(bool& baixa, int& filesEliminades);
    void mostraTextTauler();

    int const getPuntuacio() { return m_puntuacio; }
    string getNomJugador() { return m_nomJugador; }

    //MUSICA
    void pararMusica();
    //void seguentCanco();
    void reprodueixMusica(const string& musica);
    string escollirMusica();
    void llistarArxius();
    void reproduirSeguentCanco();

private:
    double m_temps;

    ////////
    Joc m_joc;
    
    int m_nivell;
    float m_incrementVelocitat; // per fer que augmenti la velocitat de caiguda de figuras
    int m_puntuacio;
    bool m_partidaAcabada; //provisional
    
    //falta atribut per guardar les figures que cauran
    //int m_mode;
    
    string m_nomJugador; // provisional, ya es veura si es necesaria
    
    list<Figura> m_figuraTest; //creem la lista per guardar les figures pel test
    list<Figura>::iterator itFigura; //iterador, per pasar les seguents figures

    list<TipusMoviment> m_movimentTest; //creem la lista per guardar els moviments pel test
    list<TipusMoviment>::iterator itMov; //iterador, per pasar les seguents figures


    //MUSICA
    static const int MAX_ARXIUS = 100;
    string m_arxiusMusica[MAX_ARXIUS];
    int m_numArxius;
    int m_indexMusicaActual;

};

#endif 
