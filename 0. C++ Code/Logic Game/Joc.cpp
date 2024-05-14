#include "Joc.h"

#include "Joc.h"

#include <fstream>

Joc::Joc()
{
	m_taulerJoc = Tauler();
	m_figuraCaient = Figura();
	m_puntuacio = 0;
	m_nivell = 0;
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream arxiu;
	arxiu.open(nomFitxer);

	if (arxiu.is_open())
	{
		//llegir la primera fila, les dades de la figura
		int fila, columna, estat, tipus;
		arxiu >> tipus >> fila >> columna >> estat;

		m_figuraCaient = Figura(static_cast<TipusFigura>(tipus), estat);
		m_figuraCaient.setPosicioX(--columna);
		m_figuraCaient.setPosicioY(--fila);

		//llegir les dades del tauler
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				int valor;
				arxiu >> valor;
				m_taulerJoc.setCasella(i, j, valor);
			}
		}

		//escriure figura al tauler
		escriuFiguraAlTauler();

		arxiu.close();
	}
}


void Joc::escriuFiguraAlTauler()
{
	int fila, columna;

	fila = m_figuraCaient.getPosicioY();
	columna = m_figuraCaient.getPosicioX();

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			int casella = m_figuraCaient.getCasellaFigura(i, j);

			if (casella != COLOR_NEGRE)
			{
				m_taulerJoc.setCasella(fila + i, columna + j, casella);
			}
		}
	}
}

void Joc::esborraFiguraDelTauler()
{
	int fila, columna;

	fila = m_figuraCaient.getPosicioY();
	columna = m_figuraCaient.getPosicioX();

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			int casella = m_figuraCaient.getCasellaFigura(i, j);

			if (casella != COLOR_NEGRE)
			{
				m_taulerJoc.setCasella(fila + i, columna + j, COLOR_NEGRE);
			}
		}
	}
}


void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream arxiu;
	arxiu.open(nomFitxer);

	if (arxiu.is_open())
	{
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				arxiu << m_taulerJoc.getCasella(i, j) << " ";
			}

			arxiu << endl;
		}

		arxiu.close();
	}
}


bool Joc::giraFigura(DireccioGir sentit)
{
	bool figuraGirada = false;

	Figura figuraSeguent = m_figuraCaient;
	//en aquest cas, comprovem si podriem possar al tauler la figura girada

	figuraSeguent.girarFigura(sentit); //actualitza l'estat que tindrien les caselles de la figura al girar

	esborraFiguraDelTauler();

	if (comprovaMoviment(figuraSeguent)) //comprovem si la figura es podra possar al tauler
	{
		//actualitzem la nostra figura amb figuraSeguent i la posem al tauler
		m_figuraCaient = figuraSeguent;

		figuraGirada = true;
	}

	escriuFiguraAlTauler();

	return figuraGirada;
}


bool Joc::mouFigura(int dirX)
{
	bool figuraMoguda = false;

	Figura figuraSeguent = m_figuraCaient;
	//en aquest cas, comprovem si podriem possar al tauler la figura moguda en una posicio (horitzontalment)

	figuraSeguent.movimentHoritzontal(dirX); //actualitza la posicio que tindria la seguent figura al tauler

	esborraFiguraDelTauler();

	if (comprovaMoviment(figuraSeguent)) //comprovem si la figura es podra possar al tauler
	{
		//actualitzem la nostra figura amb figuraSeguent i la posem al tauler
		m_figuraCaient = figuraSeguent;

		figuraMoguda = true;
	}

	escriuFiguraAlTauler();

	return figuraMoguda;
}


int Joc::baixaFigura()
{

	int filesCompletades = 0;
	Figura figuraSeguent = m_figuraCaient;
	bool haCaigut = false;

	esborraFiguraDelTauler();

	figuraSeguent.cauFigura(); //actualitza la posicio que tindria la seguent figura al tauler

	if (comprovaMoviment(figuraSeguent)) //comprovem si la figura es podra possar al tauler
	{
		//actualitzem la nostra figura amb figuraSeguent i la posem al tauler
		m_figuraCaient = figuraSeguent;

		escriuFiguraAlTauler();
	}

	else
	{
		escriuFiguraAlTauler();

		filesCompletades = m_taulerJoc.eliminarFila(m_figuraCaient.getPosicioY(), m_figuraCaient.getPosicioX()); //les y son les files, les x les columnes
	}

	return filesCompletades;
}



bool Joc::comprovaMoviment(Figura& figuraSeguent)
{
	bool movimentCorrecte = true; //Suposem que el moviment sera correcta
	int fila = 0, columna = 0;

	while ((movimentCorrecte) && (fila < MAX_ALCADA))
	{
		columna = 0; //reiniciar columna para siguiente fila
		
		while ((movimentCorrecte) && (columna < MAX_AMPLADA))
		{
			//columnes --> x (augmentar les columnes es augmentar en l'eix de les x)
			//files --> y (augmentar les files es disminuir en l'eix de les y)
			int posXFiguraAlTauler = figuraSeguent.getPosicioX() + columna;
			int posYFiguraAlTauler = figuraSeguent.getPosicioY() + fila;
			//coordenades de l'extrem supeior esquerre de la matriu de la figura al tauler

			//comprovar si la sigura seguent xoca amb alguna altra del tauler
			if ((figuraSeguent.getCasellaFigura(fila, columna) != COLOR_NEGRE) && (m_taulerJoc.getCasella(posYFiguraAlTauler, posXFiguraAlTauler) != COLOR_NEGRE))
			{
				movimentCorrecte = false;
				//si el tauler en aquella posicio es 0, llavors la casella es podra colocar
				//si no es zero, ja hi ha una altra figura i per tan, no es pot colocar
			}

			//comprovar si hi ha alguna casella de la figura que se surt del tauler
			if ((figuraSeguent.getCasellaFigura(fila, columna) != COLOR_NEGRE) && (m_taulerJoc.comprovaSiCasellaForaTauler(posYFiguraAlTauler, posXFiguraAlTauler)))
			{
				movimentCorrecte = false;
				//si la casella == 0, no pasa res, moviment correcte
				//si la casella != 0, es a dir, te color (es una casella de la figura), llavors:
					//si la casella on se surt del tauler, moviment correcte
					//si la casella se surt del tauler, error
				//si posXFiguraAlTauler o posYFiguraAlTauler son <0, error
			}

			++columna;
		}

		++fila;
	}

	return movimentCorrecte;
}