#ifndef JOC_H
#define JOC_H

#include "Figura.h"
#include <string>
using namespace std;

#include <fstream>
#include <iostream>

Figura::Figura()
{
    for (int i = 0; i < MAX_AMPLADA; i++)
    {
        for (int j = 0; j < MAX_ALCADA; j++)
        {
            m_formaFiguraActual[i][j] = COLOR_NEGRE;
        }
    }

    m_color = COLOR_NEGRE;
    m_posicioX = -1;
    m_posicioY = -1;
    m_tipus = NO_FIGURA;
}


Figura::Figura(TipusFigura tipus, int estat)
{
    string arxiu;

    m_tipus = tipus;

    for (int fila = 0; fila < MAX_ALCADA; fila++)
    {
        for (int columna = 0; columna < MAX_AMPLADA; columna++)
        {
            m_formaFiguraActual[fila][columna] = COLOR_NEGRE;
        }
    }

    switch (m_tipus)
    {
    case FIGURA_J:
        m_formaFiguraActual[0][0] = COLOR_BLAUFOSC;
        m_formaFiguraActual[1][0] = COLOR_BLAUFOSC;
        m_formaFiguraActual[1][1] = COLOR_BLAUFOSC;
        m_formaFiguraActual[1][2] = COLOR_BLAUFOSC;

        m_color = COLOR_BLAUFOSC;
        break;

    case FIGURA_L:
        m_formaFiguraActual[0][2] = COLOR_TARONJA;
        m_formaFiguraActual[1][0] = COLOR_TARONJA;
        m_formaFiguraActual[1][1] = COLOR_TARONJA;
        m_formaFiguraActual[1][2] = COLOR_TARONJA;

        m_color = COLOR_TARONJA;
        break;

    case FIGURA_T:
        m_formaFiguraActual[0][1] = COLOR_MAGENTA;
        m_formaFiguraActual[1][0] = COLOR_MAGENTA;
        m_formaFiguraActual[1][1] = COLOR_MAGENTA;
        m_formaFiguraActual[1][2] = COLOR_MAGENTA;

        m_color = COLOR_MAGENTA;
        break;

    case FIGURA_S:
        m_formaFiguraActual[0][1] = COLOR_VERD;
        m_formaFiguraActual[0][2] = COLOR_VERD;
        m_formaFiguraActual[1][0] = COLOR_VERD;
        m_formaFiguraActual[1][1] = COLOR_VERD;

        m_color = COLOR_VERD;
        break;

    case FIGURA_Z:
        m_formaFiguraActual[0][0] = COLOR_VERMELL;
        m_formaFiguraActual[0][1] = COLOR_VERMELL;
        m_formaFiguraActual[1][1] = COLOR_VERMELL;
        m_formaFiguraActual[1][2] = COLOR_VERMELL;

        m_color = COLOR_VERMELL;
        break;

    case FIGURA_I:
        m_formaFiguraActual[1][0] = COLOR_BLAUCEL;
        m_formaFiguraActual[1][1] = COLOR_BLAUCEL;
        m_formaFiguraActual[1][2] = COLOR_BLAUCEL;
        m_formaFiguraActual[1][3] = COLOR_BLAUCEL;

        m_color = COLOR_BLAUCEL;
        break;

    case FIGURA_O:
        m_formaFiguraActual[0][0] = COLOR_GROC;
        m_formaFiguraActual[0][1] = COLOR_GROC;
        m_formaFiguraActual[1][0] = COLOR_GROC;
        m_formaFiguraActual[1][1] = COLOR_GROC;

        m_color = COLOR_GROC;
        break;
    default:
        break;
    }


    //COLOCA LA FIGURA A L'ESTAT DESITJAT
    if (estat == 3)
    {
        girarFigura(GIR_ANTI_HORARI);
    }

    else
    {
        for (int i = 0; i < estat; i++)
        {
            girarFigura(GIR_HORARI);
        }
    }
}

void Figura::posicionsFigures(const string& nomArxiu)
{
    ifstream arxiu;
    arxiu.open(nomArxiu);

    if (arxiu.is_open())
    {
        for (int i = 0; i < MAX_AMPLADA; i++)
        {
            for (int j = 0; j < MAX_ALCADA; j++)
            {
                arxiu >> m_formaFiguraActual[i][j];
            }
        }
    }

    arxiu.close();
}


void Figura::girarFigura(DireccioGir sentit)
{
    int nFilesFigura, nColumnesFigura;

    if (m_tipus != FIGURA_O) //LA FIGURA_O (EL QUADRAT) QUAN GIRA ES QUEDA IGUAL
    {
        //ASSIGNA EL NOMBRE DE FILES I COLUMNES DE LA MATRIU QUE OCUPA LA FIGURA AL GIRAR
        if (m_tipus == FIGURA_I)
        {
            nFilesFigura = MAX_ALCADA;
            nColumnesFigura = MAX_AMPLADA;
        }

        else
        {
            nFilesFigura = 3;
            nColumnesFigura = 3;
        }

        //GIRAR LA MATTRTIU EN FUNCIO DEL SENTIT DEL GIR
        if (sentit == GIR_HORARI)
        {
            //GIRA LA MATRIU 90 GRAUS EN SENTIT HORARI
            for (int fila = 0; fila < nFilesFigura / 2; fila++)
            {
                for (int columna = fila; columna < nColumnesFigura - 1 - fila; columna++)
                {
                    int numTemporal = m_formaFiguraActual[fila][columna];

                    m_formaFiguraActual[fila][columna] = m_formaFiguraActual[nFilesFigura - 1 - columna][fila];
                    m_formaFiguraActual[nFilesFigura - 1 - columna][fila] = m_formaFiguraActual[nFilesFigura - 1 - fila][nColumnesFigura - 1 - columna];
                    m_formaFiguraActual[nFilesFigura - 1 - fila][nColumnesFigura - 1 - columna] = m_formaFiguraActual[columna][nColumnesFigura - 1 - fila];
                    m_formaFiguraActual[columna][nColumnesFigura - 1 - fila] = numTemporal;
                }
            }
        }
        else //GIR_ANTI_HORARI
        {
            //GIRA LA MATRIU 90 GRAUS EN SENTIT ANTIHORARI
            for (int fila = 0; fila < nFilesFigura / 2; fila++)
            {
                for (int columna = fila; columna < nColumnesFigura - 1 - fila; columna++)
                {
                    int numTemporal = m_formaFiguraActual[fila][columna];

                    m_formaFiguraActual[fila][columna] = m_formaFiguraActual[columna][nColumnesFigura - 1 - fila];
                    m_formaFiguraActual[columna][nColumnesFigura - 1 - fila] = m_formaFiguraActual[nFilesFigura - 1 - fila][nColumnesFigura - 1 - columna];
                    m_formaFiguraActual[nFilesFigura - 1 - fila][nColumnesFigura - 1 - columna] = m_formaFiguraActual[nColumnesFigura - 1 - columna][fila];
                    m_formaFiguraActual[nFilesFigura - 1 - columna][fila] = numTemporal;
                }
            }
        }
    } 
}


void Figura::movimentHoritzontal(int direccio)
{
    m_posicioX += direccio;
    //si volem anar a la dreta, direccio=1, m_posicio augmenta en 1
    //si volem anar a la esquerra, direccio = -1, m_posicio disminueix en 1
}

void Figura::cauFigura()
{
    ++m_posicioY;
    //com la figura esta caient, la figura descendeix cap a valors mes grans de Y, per tant augmentem la posicio Y
}

#endif
