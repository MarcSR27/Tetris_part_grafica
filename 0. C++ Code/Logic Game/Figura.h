#ifndef FIGURA_H
#define FIGURA_H

using namespace std;
#include <string>

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;

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


private:
    int m_formaFiguraActual[MAX_AMPLADA][MAX_ALCADA];

    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_posicioX; //coordenada x del quadrat pivot de la figura
    int m_posicioY; //coordenada y del quadrat pivot de la figura
};


#endif