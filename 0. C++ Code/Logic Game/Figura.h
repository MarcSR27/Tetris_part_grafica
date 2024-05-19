#ifndef FIGURA_H
#define FIGURA_H

using namespace std;
#include <string>
#include "InfoJoc.h"

const int MAX_AMPLADA = 4;
const int MAX_ALCADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    Figura();
    Figura(TipusFigura tipus, int estat);

    void movimentHoritzontal(int direccio);
    void cauFigura();

    void girarFigura(DireccioGir sentit);
    void posicionsFigures(const string& nomArxiu);

    //GETERS I SETERS
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }
    void setColor(ColorFigura color) { m_color = color; }
    void setPosicioX(int posicioX) { m_posicioX = posicioX; }
    void setPosicioY(int posicioY) { m_posicioY = posicioY; }
    TipusFigura getTipus() { return m_tipus; }
    ColorFigura getColor() { return m_color; }
    int getPosicioX() { return m_posicioX; }
    int getPosicioY() { return m_posicioY; }
    int getCasellaFigura(int fila, int columna) { return m_formaFiguraActual[fila][columna]; }


    //segona Part
    void dibuixaFigura();

    /*
    const int(&getFormaFiguraActual())[MAX_ALCADA][MAX_AMPLADA]
    {
        return m_formaFiguraActual;
    }
    void setFigura(int figura[MAX_AMPLADA][MAX_ALCADA])
    {
        for (int fila = 0; fila < MAX_AMPLADA; fila++)
        {
            for (int col = 0; col < MAX_ALCADA; col++)
            {
                figura[fila][col] = m_formaFiguraActual[fila][col];
            }
        }
    }*/


private:
    int m_formaFiguraActual[MAX_AMPLADA][MAX_ALCADA];

    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_posicioX; //coordenada x del quadrat pivot de la figura
    int m_posicioY; //coordenada y del quadrat pivot de la figura
};


#endif