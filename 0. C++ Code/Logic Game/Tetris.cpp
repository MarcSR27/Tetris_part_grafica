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
    string musica = "data\\Audio\\" + m_partida.getCanco();

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
            resposta = controlResposta();

            if (resposta == 's')
            {
                system("cls");
                cout << flush;
                opcio = -1;
            }
            else
            {
                estaJugant = false;
                missatgeFinal();
            }
            break;

        case 4: //Menu de musica
            
            estaJugant = menuMusica(opcio, musica);
            break;

        case 5: 
            
            missatgeFinal();
            estaJugant = false; 
            break;

        default: 
            cout << "Tens que escriure el numero d'una de les opcions (1, 2, 3, 4, 5)" << endl;
            break;
        }

    } while ((opcio != 1) and (opcio != 2) and (opcio != 3) and (opcio != 4) and (opcio != 5));

    if (estaJugant)
    {
        m_partida.pararMusica();

        m_partida.reprodueixMusica(musica);
    }

    return estaJugant;
}


bool Tetris::menuMusica(int& opcio, string& musica)
{
    bool estaJugant = true;
    int opcio2;

    musica = m_partida.escollirMusica(opcio2);

    if (opcio2 != 0)
    {
        cout << "Vols tornar al menu? (s/n)" << endl;

        char resposta2;
        resposta2 = controlResposta();

        if (resposta2 == 's')
        {
            opcio = -1;
        }
        else
        {
            estaJugant = false;
            missatgeFinal();
        }
    }
    else
    {
        opcio = -1;
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

    cout << "Vols guardar la teva puntuacio? (s/n)" << endl;

    resposta = controlResposta();

    if (resposta == 's')
    {
        m_partida.escriuPuntuacio(fitxerPuntuacions);
    }

    //gestiona si jugar una altra partida
    bool final = false;
    cout << endl << "Vols tornar al menu principal? (s/n)" << endl;

    resposta = controlResposta();

    if (resposta == 's')
    {
        final = true;
    }
    else
    {
        missatgeFinal();
    }

    return final;
}

void Tetris::imprimirMenu()
{
    system("cls");
    cout << flush;

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
    system("cls");
    cout << flush;

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

char Tetris::controlResposta()
{
    char resposta;

    cin >> resposta;

    while ((resposta != 's') && (resposta != 'n'))
    {
        cout << "Resposta no valida. Escriu s (si) o n (no): " << endl;
        cin >> resposta;
    }

    return resposta;
}