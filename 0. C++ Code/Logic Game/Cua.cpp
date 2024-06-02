#include "cua.h"
using namespace std;

void CuaFigura::afegeix(const Figura fig)
{
	NodeFigura* nouNode = new NodeFigura; //creem nou node
	nouNode->setValor(fig); //assignem valor al node nou
	nouNode->setNext(nullptr); //apunta a nullptr la nova figura

	if (m_punterFigIni == nullptr) //si la cua es buida
	{
		m_punterFigIni = nouNode;
		m_punterFigFi = nouNode; //assignem nouNode com a final de la cua
	}
	else
	{
		m_punterFigFi->setNext(nouNode); //nouNode es coloca darrere de l'anterior node
		m_punterFigFi = nouNode; //nouNode a final de la cua en tots el casos
	}
}

void CuaFigura::elimina()
{
	if (!buit())
	{
		NodeFigura* seguentNode = m_punterFigIni;
		m_punterFigIni = m_punterFigIni->getNext();
		delete seguentNode;
	}
}

bool CuaFigura::buit()
{
	return m_punterFigIni == nullptr; //si es buit apunta a nullptr i sera true
}

CuaFigura::~CuaFigura()
{
	while (!buit())
	{
		elimina();
	}
}


// cua moviments

void CuaMov::afegeix(const TipusMoviment mov)
{
	NodeMov* nouNode = new NodeMov; //creem nou node
	nouNode->setValor(mov); //assignem valor al node nou
	nouNode->setNext(nullptr); //apunta a nullptr el nou moviment

	if (m_punterMovIni == nullptr) //si la cua es buida
	{
		m_punterMovIni = nouNode;
		m_punterMovFi = nouNode; //assignem nouNode com a final de la cua
	}
	else
	{
		m_punterMovFi->setNext(nouNode); //nouNode es coloca darrere de l'anterior node
		m_punterMovFi = nouNode; //nouNode a final de la cua en tots el casos
	}
}

void CuaMov::elimina()
{
    if (!buit())
    {
        NodeMov* seguentNode = m_punterMovIni;
        m_punterMovIni = m_punterMovIni->getNext();
        delete seguentNode;
    }
}

bool CuaMov::buit()
{
	return m_punterMovIni == nullptr; //si es buit apunta a nullptr i sera true
}
CuaMov::~CuaMov()
{
	while (!buit())
	{
		elimina();
	}
}