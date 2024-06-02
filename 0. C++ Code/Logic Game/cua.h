#ifndef cua_h
#define cua_h

#include "Node.h"

using namespace std;

class CuaFigura
{
private:
	NodeFigura* m_punterFigIni ;
	NodeFigura* m_punterFigFi = nullptr;
public:
	CuaFigura(): m_punterFigIni(nullptr), m_punterFigFi(nullptr) {}
	~CuaFigura();

	
	Figura getPrimerFig()
	{
		if (m_punterFigIni != nullptr)
		{
			Figura figuraPrimer = m_punterFigIni->getValor();

			return figuraPrimer;
		}	
	}

	void afegeix(const Figura fig);
	void elimina();
	bool buit();
};



class CuaMov
{
private:
	NodeMov* m_punterMovIni;
	NodeMov* m_punterMovFi;
public:
	CuaMov() : m_punterMovIni(nullptr), m_punterMovFi(nullptr) {}
	~CuaMov();


	TipusMoviment getPrimerMov()
	{
		if (m_punterMovIni != nullptr)
		{
			TipusMoviment movPrimer = m_punterMovIni->getValor();

			return movPrimer;
		}
	}

	void afegeix(const TipusMoviment mov);
	void elimina();
	bool buit();
};
#endif // 