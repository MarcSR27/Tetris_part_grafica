#include "Tauler.h"
#include <fstream>

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
/*	bool casellaFora = true;

	if ((fila >= 0) && (fila < MAX_FILA) && (columna >= 0) && (columna < MAX_COL))
	{
		casellaFora = false;
	}
	return casellaFora */

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