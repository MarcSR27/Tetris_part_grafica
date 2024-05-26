#include "Tetris.h"

Tetris::Tetris()
{
    m_partida = Partida();
    m_mode = -1;
}

void Tetris::inicialitza(string const fitxerInicial, string const fitxerFigures, string const fitxerMov)
{
    m_partida.inicialitza(m_mode, fitxerInicial, fitxerFigures, fitxerMov); 
}

bool Tetris::menuInicial(string const fitxerPuntuacions)
{
    int opcio;
    bool estaJugant = true;
    do
    {
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "Selecciona una opcio:" << endl << endl;
        cout << "1. Jugar mode normal" << endl;
        cout << "2. Jugar mode test" << endl;
        cout << "3. Visualitzar llista de millors puntuacions" << endl;
        cout << "4. Sortir del programa" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;

        cin >> opcio;
        switch (opcio)
        {
        case 1: m_mode = 0; break;
        case 2: m_mode = 1; break;
        case 3: m_partida.mostraPuntuacio(fitxerPuntuacions);
            cout << "Vols tornar al menu? (s/n)" << endl;
            char resposta;
            cin >> resposta;
            if (resposta == 's')
            {
                opcio = -1;
            }
            else
            {
                estaJugant = false;
            }
            break;
        case 4: estaJugant = false; break;
        default: cout << "Tens que escriure el numero d'una de les opcions (1, 2, 3, 4)" << endl;  break;
        }

    } while ((opcio != 1) and (opcio != 2) and (opcio != 3) and (opcio != 4));

    return estaJugant;
}

void Tetris::juga(double const deltaTime)
{
    m_partida.actualitza(m_mode, deltaTime);
}


bool Tetris::finalPartida(string const fitxerPuntuacions)
{
    char resposta;
    cout << "Vols guardar la teva puntuacio? (s/n)" << endl;
    cin >> resposta;
    if (resposta == 's')
    {
        m_partida.escriuPuntuacio(fitxerPuntuacions);
    }

    //gestiona si jugar una altra partida
    bool final = false;
    cout << endl << "Vols tornal al menu principal?(s/n)" << endl;
    cin >> resposta;
    if (resposta == 's')
    {
        final = true;
    }

    return final;
}
