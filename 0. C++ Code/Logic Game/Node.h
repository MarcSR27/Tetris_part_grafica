
#include "Figura.h"
#include "InfoJoc.h"

class NodeFigura
{
public:
	Figura getValor() { return m_figura; }
	NodeFigura* getNext() { return m_nextFigura; }
	void setValor(const Figura fig) { m_figura = fig; }
	void setNext(NodeFigura* nextFig) { m_nextFigura = nextFig; }
private:
	Figura m_figura;
	NodeFigura* m_nextFigura;
};

class NodeMov
{
public:
	TipusMoviment getValor() { return m_mov; }
	NodeMov* getNext() { return m_nextMov; }
	void setValor(const TipusMoviment mov) { m_mov = mov; }
	void setNext(NodeMov* nextMov) { m_nextMov = nextMov; }
private:
	TipusMoviment m_mov;
	NodeMov* m_nextMov;
};