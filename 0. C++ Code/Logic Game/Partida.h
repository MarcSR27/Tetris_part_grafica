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

#include "cua.h"

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
    void gestionaNovaPuntuacio(const string& nomFitxer, list<Jugador> puntuacions);

    void accionsTeclat(bool& baixa, int& filesEliminades);
    void mostraTextTauler();
    void figuraPosadaAlTauler(int mode);

    int const getPuntuacio() { return m_puntuacio; }
    string getNomJugador() { return m_nomJugador; }

    //MUSICA
    void pararMusica();
    string getCanco() const { return m_arxiusMusica[m_indexMusicaActual]; }
    void reprodueixMusica(const string& musica);
    string escollirMusica(int& opcio);
    void llistarArxius();
    void reproduirSeguentCanco();

private:
    double m_temps;

    ////////
    Joc m_joc;
    
    int m_nivell;
    float m_incrementVelocitat; 
    int m_puntuacio;
    bool m_partidaAcabada; 
    
    string m_nomJugador; 
 
    CuaFigura m_figuraTest;
    CuaMov m_movimentTest;

    //MUSICA
    static const int MAX_ARXIUS = 100;
    string m_arxiusMusica[MAX_ARXIUS];
    int m_numArxius;
    int m_indexMusicaActual;

};

#endif 
