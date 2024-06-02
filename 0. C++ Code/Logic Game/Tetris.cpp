    #include "Tetris.h"
#include <cstdlib>

#include <iostream>

#include <mmsystem.h> // Incluir esta cabecera para mciSendString
#pragma comment(lib, "winmm.lib")

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
    m_partida.pararMusica();
    m_partida.reprodueixMusica("data\\Audio\\title.mp3");
    
    int opcio;
    bool estaJugant = true;
    string musica = "data\\Audio\\Tetris.mp3";

    do
    {
        imprimirMenu();

        cin >> opcio;

        switch (opcio)
        {
        case 1: //Modo jugar partida
            m_mode = 0; 
            break;


        case 2: //Modo partida tes
            m_mode = 1; 
            break;


        case 3:  //Mostrar puntuaciones 
            
            m_partida.mostraPuntuacio(fitxerPuntuacions);
            cout << "Vols tornar al menu? (s/n)" << endl;
            char resposta;
            cin >> resposta;

            if (resposta == 's')
            {
                system("cls");
                cout << flush;
                opcio = -1;
            }
            else
            {
                estaJugant = false;
            }
            break;

        case 4: //Menu de musica
            
            musica = m_partida.escollirMusica();
            cout << "Vols tornar al menu? (s/n)" << endl;
            char resposta2;
            cin >> resposta2;
            if (resposta2 == 's')
            {
                system("cls");
                cout << flush;
                opcio = -1;
            }
            else
            {
                estaJugant = false;
            }
            break;

        case 5: missatgeFinal();
            estaJugant = false; 
            break;

        default: 
            cout << "Tens que escriure el numero d'una de les opcions (1, 2, 3, 4, 5)" << endl;
            break;
        }

    } while ((opcio != 1) and (opcio != 2) and (opcio != 3) and (opcio != 4) and (opcio != 5));

    if ((estaJugant) && (musica != ""))
    {
        m_partida.pararMusica();

        m_partida.reprodueixMusica(musica);
    }

    return estaJugant;
}

void Tetris::juga(double const deltaTime)
{
    m_partida.actualitza(m_mode, deltaTime);
}


bool Tetris::finalPartida(string const fitxerPuntuacions)
{
    char resposta;
    
    //if (m_mode != 1)
    {
        cout << "Vols guardar la teva puntuacio? (s/n)" << endl;
        cin >> resposta;
        if (resposta == 's')
        {
            m_partida.escriuPuntuacio(fitxerPuntuacions);
        }
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

void Tetris::imprimirMenu()
{
    cout << "___ TETRIS ___" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "Selecciona una opcio:" << endl << endl;
    cout << "1. Jugar mode normal" << endl;
    cout << "2. Jugar mode test" << endl;
    cout << "3. Visualitzar llista de millors puntuacions" << endl;
    cout << "4. Llista de musica de fons" << endl;
    cout << "5. Sortir del programa" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
}


void Tetris::missatgeFinal()
{
    m_partida.pararMusica();
    m_partida.reprodueixMusica("data\\Audio SoundEffects\\dad-says-bye-bye-113119.mp3");

    cout << "SORTINT DEL JOC ";

    for (int i = 0; i < 3; i++)
    {
        Sleep(500);
        cout << ". ";
    }

    cout << endl << endl << "FINS AVIAT!!! :)";
    Sleep(1000);
}