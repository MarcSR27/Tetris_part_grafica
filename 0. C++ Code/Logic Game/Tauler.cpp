#include "Tauler.h"
#include <fstream>

#include "InfoJoc.h"
#include "GraphicManager.h"

Tauler::Tauler()
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			m_tauler[i][j] = COLOR_NEGRE;
		}
	}
}


void Tauler::setCasella(int fila, int columna, int valor)
{
	m_tauler[fila][columna] = static_cast<ColorFigura>(valor);
}

int Tauler::getCasella(int fila, int columna)
{
	int valor = static_cast<int>(m_tauler[fila][columna]);

	return valor;
}

int Tauler::eliminarFila(int const fila, int const columna)
{
	int i = fila, filesCompletades = 0;

	if (m_tauler[fila][columna] == COLOR_ROSA) // bomba que elimina un quadrat 9x9
	{
		m_tauler[fila][columna] = COLOR_NEGRE;   //Cal comprovar totes les posibilitats
		if (fila >= 0 && fila < MAX_FILA && columna >= 0 && columna < MAX_COL) {
			m_tauler[fila][columna] = COLOR_NEGRE;
		}
		if (fila - 1 >= 0) {
			m_tauler[fila - 1][columna] = COLOR_NEGRE;
		}
		if (fila + 1 < MAX_FILA) {
			m_tauler[fila + 1][columna] = COLOR_NEGRE;
		}
		if (fila - 1 >= 0 && columna - 1 >= 0) {
			m_tauler[fila - 1][columna - 1] = COLOR_NEGRE;
		}
		if (fila - 1 >= 0 && columna + 1 < MAX_COL) {
			m_tauler[fila - 1][columna + 1] = COLOR_NEGRE;
		}
		if (columna - 1 >= 0) {
			m_tauler[fila][columna - 1] = COLOR_NEGRE;
		}
		if (columna + 1 < MAX_COL) {
			m_tauler[fila][columna + 1] = COLOR_NEGRE;
		}
		if (fila + 1 < MAX_FILA && columna - 1 >= 0) {
			m_tauler[fila + 1][columna - 1] = COLOR_NEGRE;
		}
		if (fila + 1 < MAX_FILA && columna + 1 < MAX_COL) {
			m_tauler[fila + 1][columna + 1] = COLOR_NEGRE;
		}

	}
	while ((i < fila + MAX_ALCADA) && (i < MAX_FILA))
	{
		int j = 0;
		bool eliminaFila = true;

		while ((j < MAX_COL) && (eliminaFila))
		{
			if (m_tauler[i][j] == COLOR_NEGRE) //comprova les columnes si la fila no es plena
			{
				eliminaFila = false;
			}

			++j;
		}

		if (eliminaFila)
		{
			++filesCompletades;

			for (int k = i; k >= 0; k--)
			{
				for (int z = 0; z < MAX_COL; z++)
				{
					if (k == 0) //comprovaba si es la primera fila
					{
						m_tauler[0][z] = COLOR_NEGRE; //posa a COLOR_NEGRE al primera fila
					}
					else
					{
						m_tauler[k][z] = m_tauler[k - 1][z]; //baixa les files superiors
					}
				}
			}
		}
		else
		{
			++i;
		}
	}

	return filesCompletades;
}


void Tauler::guardaTauler(string nomFitxer) // per saber quin tauler tenim en els test
{
	ifstream arxiu;
	arxiu.open(nomFitxer);
	if (arxiu.is_open())
	{
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				arxiu >> m_tauler[i][j];
			}
		}
	}
}


bool Tauler::comprovaSiCasellaForaTauler(int fila, int columna)
{
	return !((fila >= 0) && (fila < MAX_FILA) && (columna >= 0) && (columna < MAX_COL)); //Si esta fora de la casella retorna true, sino false
}


void Tauler::actualitzaTauler(Figura figura)
{
	int i = 0, j = 0;

	for (int fila = figura.getPosicioY(); fila < MAX_ALCADA; fila++)
	{
		j = 0;

		for (int columna = figura.getPosicioX(); columna < MAX_AMPLADA; columna++)
		{
			m_tauler[fila][columna] = figura.getCasellaFigura(i, j);
			++j;
		}

		++i;
	}
}

void Tauler::dibuixaTauler()
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (m_tauler[i][j] != COLOR_NEGRE)
			{
				IMAGE_NAME bloc = GRAFIC_FONS;
				switch (m_tauler[i][j])
				{
				case COLOR_GROC: bloc = GRAFIC_QUADRAT_GROC; break;
				case COLOR_BLAUCEL: bloc = GRAFIC_QUADRAT_BLAUCEL; break;
				case COLOR_MAGENTA: bloc = GRAFIC_QUADRAT_MAGENTA; break;
				case COLOR_TARONJA: bloc = GRAFIC_QUADRAT_TARONJA; break;
				case COLOR_BLAUFOSC: bloc = GRAFIC_QUADRAT_BLAUFOSC; break;
				case COLOR_VERMELL: bloc = GRAFIC_QUADRAT_VERMELL; break;
				case COLOR_VERD: bloc = GRAFIC_QUADRAT_VERD; break;
				case COLOR_ROSA: bloc = GRAFIC_QUADRAT_ROSA; break;
				case COLOR_BLANC: bloc = GRAFIC_QUADRAT_BLANC; break;
				}

				GraphicManager::getInstance()->drawSprite(bloc, POS_X_TAULER + ((1 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((i)*MIDA_QUADRAT), false);
			}
		}
	}
}