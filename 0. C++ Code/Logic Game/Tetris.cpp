#include "Tetris.h"

void Tetris::inicialitza()
{
	m_partida.figuraAleatoria();
}
/*
void Tetris::menuInicial()
{
    int opcio;
    bool estaJugant = true;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "Selecciona una opcio:" << endl << endl;
    cout << "1. Jugar mode normal" << endl;
    cout << "2. Jugar mode test" << endl;
    cout << "3. Visualitzar llista de millors puntuacions" << endl;
    cout << "4. Sortir del programa" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    do
    {
        cin >> opcio;
        switch (opcio)
        {
        case 1: mode = 0; break;
        case 2: mode = 1; break;
        case 3: // visualitzar llista puntuacions; break;
        case 4: estaJugant = false; break;
        default: cout << "Tens que escriure el numero d'una de les opcions (1, 2, 3, 4)" << endl;  break;
        }
    } while ((opcio != 1) and (opcio != 2) and (opcio != 3) and (opcio != 4));
}*/