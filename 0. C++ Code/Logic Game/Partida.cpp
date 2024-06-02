#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <string>


#include <mmsystem.h> // Incluir esta cabecera para mciSendString
#pragma comment(lib, "winmm.lib")


Partida::Partida()
{

    m_puntuacio = 0;
    m_nivell = 0;
    m_temps = 0;
    m_incrementVelocitat = 0;

    m_joc = Joc();
    m_partidaAcabada = false;

    llistarArxius();
}

void Partida::inicialitza(int const mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (mode == 1) //mode test
    {

        //INICIALITZA EL TAULER A BUIT
        m_joc = Joc();
        m_joc.inicialitzaTaulerTest(fitxerInicial, m_figuraTest);

        m_joc.inicialitzaFiguresTest(fitxerFigures, m_figuraTest);

        if (!m_figuraTest.buit())
        {
            Figura figuraTest = m_figuraTest.getPrimerFig(); //accedemos a la figura en la posición frontal de la cola
            m_joc.setFigura(figuraTest.getPosicioX(), figuraTest.getTipus(), figuraTest.getEstat(), figuraTest.getPosicioY());
            m_figuraTest.elimina(); //eliminem el primer node
        }
        
        m_joc.inicialitzaMovimentsTest(fitxerMoviments, m_movimentTest);

    }
    else //mode normal
    {
        //INICIALITZA EL TAULER A BUIT
        m_joc = Joc();

        //GENERA ALEATORIAMENT UNA FIGURA
        int estat, columna;
        TipusFigura tipusFigura;
        
        do
        {
            tipusFigura = generarTipusFiguraAleatoria(); //No sale la figura hasta que se genere bien
            columna = generarNumAleatori(0, MAX_COL - 1);
            estat = generarNumAleatori(0, 3);

        } while (!m_joc.setFigura(columna, tipusFigura, estat, 0) and tipusFigura != FIGURA_BOMBA); // fila = 0, evita que la primera figura sigui la Bomba

        m_joc.setFigura(columna, tipusFigura, estat, 0);
    }

    m_nivell = 1;
    m_incrementVelocitat = 1;
    m_puntuacio = 0;
    m_temps = 0;
    m_partidaAcabada = false;
    m_nomJugador = "";
}

void Partida::puntuacioINivell(int const filesEliminades)
{
    if (!m_partidaAcabada)
    {
        int puntsExtra = 0;

        //ACTUALITZA PUNTUACIO
        if (filesEliminades == 1)
        {
            puntsExtra = 100;
        }
        else if (filesEliminades > 4)
        {
            puntsExtra = 300;
        }
        else if (filesEliminades != 0) //quan s'eliminen 2, 3 o 4 files a la vegada
        {
            puntsExtra = (filesEliminades * 25) + 100;
        }

        m_puntuacio += (10 + puntsExtra);

        //ACTUALITZA NIVELL
        if (m_puntuacio >= m_nivell * 500)
        {
            ++m_nivell;
            m_incrementVelocitat = m_incrementVelocitat + m_incrementVelocitat * 0.25;
            //AUGMENTA LA VELOCITAT

        }
    }
}

void Partida::figuraAleatoria()
{
    int estat, columna;
    TipusFigura tipusFigura;

    do
    {

        tipusFigura = generarTipusFiguraAleatoria();
        columna = generarNumAleatori(0, MAX_COL - 1);
        estat = generarNumAleatori(0, 3);


    } while (!m_joc.setFigura(columna, tipusFigura, estat, 0));
}

int Partida::generarNumAleatori(int min, int max)  // genera posicio aleatoria quan baixa la figura
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max); //genera posicio random entre columnes 1 i ultima
    return distrib(gen);
}

TipusFigura Partida::generarTipusFiguraAleatoria(/*TipusFigura min, TipusFigura max*/)  // genera una figura aleatoria
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(static_cast<int>(TipusFigura::FIGURA_O), static_cast<int>(TipusFigura::FIGURA_U));
    int valorAleatorio = distrib(gen);

    return static_cast<TipusFigura>(valorAleatorio); //Pasar de int a Tipus Figura, que no deixaba retornar
}


void Partida::accionsTeclat(bool& baixa, int& filesEliminades)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
    {
        m_joc.mouFigura(1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
    {
        m_joc.mouFigura(-1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
    {
        m_joc.giraFigura(GIR_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
    {
        m_joc.giraFigura(GIR_ANTI_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        do
        {
            baixa = m_joc.baixaFigura(filesEliminades);
        } while (baixa);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_RETURN))
    {
        pararMusica();
        reproduirSeguentCanco();
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
    {
        pararMusica();
    }
}


void Partida::mostraTextTauler()
{
    if (!m_partidaAcabada)
    {
        string puntuacio = "Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 260, POS_Y_TAULER - 60, 1.0, puntuacio);

        string nivell = "Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER + 260, POS_Y_TAULER - 90, 1.0, nivell);
    }
    else
    {
        string msg = "Puntuacio Final: " + to_string(m_puntuacio) + ", Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

        string fi = "___ GAME OVER ___";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER - 50, POS_Y_TAULER, 1.5, fi);
    }
}

void Partida::actualitza(int const mode, double deltaTime)
{
    if (mode == 1 and (m_figuraTest.buit() or m_movimentTest.buit()))
    {
        while (!m_figuraTest.buit())
        {
            m_figuraTest.elimina();
        }
        while (!m_movimentTest.buit())
        {
            m_movimentTest.elimina();
        }
        m_partidaAcabada = true;
    }
    int filesEliminades = 0;
    bool baixa = true;

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();

    //ACCIONS DE TECLAT
    if (mode == 0) // mode normal = 0, pots moure tu
    {
        accionsTeclat(baixa, filesEliminades);
    }
    else if (!m_movimentTest.buit())
    {
        switch (m_movimentTest.getPrimerMov())
        {
        case 0: m_joc.mouFigura(-1); break;
        case 1: m_joc.mouFigura(1); break;
        case 2: m_joc.giraFigura(GIR_HORARI); break;
        case 3: m_joc.giraFigura(GIR_ANTI_HORARI); break;
        case 4: baixa = m_joc.baixaFigura(filesEliminades); break;
        case 5: do
        {
            baixa = m_joc.baixaFigura(filesEliminades);
        } while (baixa);
        break;
        default: baixa = m_joc.baixaFigura(filesEliminades); break; //posem per defecte que baixi
        }

        m_movimentTest.elimina();
    }


    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();


    if (baixa && mode == 0) // si es mode test NO baixa automaticament
    {
        //BAIXAR FIGURA
        m_temps = m_temps + deltaTime * m_incrementVelocitat;
        if (m_temps > 0.5)
        {
            baixa = m_joc.baixaFigura(filesEliminades);

            m_temps = 0.0;
        }

        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        m_joc.dibuixa();
    }


    //MOSTRAR TEXT
    mostraTextTauler();

    if (!baixa) //la figura s'ha posat al tauler
    {
        puntuacioINivell(filesEliminades);

        if (m_joc.getFilaFigura() == 0) // revisar, provisional
        {
            if (!m_partidaAcabada)
            {
                pararMusica();
                reprodueixMusica("data\\Audio SoundEffects\\game-over-arcade-6435.mp3");
            }

            //s'ha acabat la partida
            m_partidaAcabada = true;
        }
        else if (mode == 0)//generem la seguent figura aleatoria al mode normal
        {
            figuraAleatoria();
        }
        else // estem en mode test
        {
            if (!m_figuraTest.buit())
            {
                Figura figuraTest = m_figuraTest.getPrimerFig(); //accedemos a la figura en la posición frontal de la cola
                m_joc.setFigura(figuraTest.getPosicioX(), figuraTest.getTipus(), figuraTest.getEstat(), figuraTest.getPosicioY());
                m_figuraTest.elimina(); //eliminem el primer node
            }
            else if (m_figuraTest.buit()) //si han sortit totes les figures
            {
                pararMusica();

                if (!m_partidaAcabada)
                {
                    reprodueixMusica("data\\Audio SoundEffects\\game-over-arcade-6435.mp3");
                }

                m_partidaAcabada = true;
            }
        }
    }
}


void Partida::escriuPuntuacio(const string& nomFitxer) // Separa en dues funcions, es queda aixi provisional
{
    ifstream fitxer(nomFitxer);
    list<Jugador> puntuacions; //llista on aniran el nom del jugador i les puntuacions
    if (fitxer.is_open())
    {
        string nomJugador;
        int puntuacio;
        fitxer >> nomJugador >> puntuacio;
        while (!fitxer.eof())
        {
            puntuacions.push_back({ nomJugador, puntuacio });
            fitxer >> nomJugador >> puntuacio;
        }
    }
    fitxer.close();

    cout << "Introdueix el teu nom: " << endl;
    cin >> m_nomJugador;

    puntuacions.push_back({ m_nomJugador, m_puntuacio });

    for (list<Jugador>::iterator it = puntuacions.begin(); it != puntuacions.end(); ++it)
    {
        for (list<Jugador>::iterator it2 = next(it); it2 != puntuacions.end(); ++it2)
        {
            if (it2->puntuacio > it->puntuacio)
            {
                swap(it->nom, it2->nom);
                swap(it->puntuacio, it2->puntuacio);
            }
        }
    }

    ofstream fitxerEscritura(nomFitxer);
    if (fitxerEscritura.is_open())
    {
        for (list<Jugador>::iterator it = puntuacions.begin(); it != puntuacions.end(); ++it)
        {
            fitxerEscritura << it->nom << " " << it->puntuacio << endl;
        }
        fitxerEscritura.close();
    }


}

void Partida::mostraPuntuacio(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        string nomJugador;
        int puntuacio;
        fitxer >> nomJugador >> puntuacio;
        cout << endl;
        cout << " Top 10 millors puntuacions:" << endl;
        int i = 0;
        cout << "------------------------------------------------------------" << endl;
        while (!fitxer.eof() and i <= 10)
        {
            cout << nomJugador << " " << puntuacio << endl;
            fitxer >> nomJugador >> puntuacio;
            i++;
        }
        cout << "------------------------------------------------------------" << endl;
    }
    fitxer.close();
}


void Partida::pararMusica()
{
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);
}

void Partida::reprodueixMusica(const string& musica)
{
    string comanda = "open \"" + musica + "\" type mpegvideo alias musica";

    if (mciSendString(comanda.c_str(), NULL, 0, NULL) != 0)
    {
        std::cerr << "Error al carregar l'arxiuo de musica: " << musica << std::endl;
    }
    else
    {
        string modeReproduccio = "play musica";

        if (musica.find("SoundEffects") == string::npos)
        {
            modeReproduccio += " repeat";
        }

        mciSendString(modeReproduccio.c_str(), NULL, 0, NULL);
    }
}


string Partida::escollirMusica()
{
    int opcio;

    //mostra arxius musica
    cout << "FUNCIONAMENT: Pulsa ENTER duran la partida per passar a la seguent canco: " << endl << endl;

    cout << endl << "Musica disponible: " << endl;
    for (int i = 0; i < m_numArxius; i++)
    {
        cout << i + 1 << ". " << m_arxiusMusica[i] << endl;
    }

    cin >> opcio;

    m_indexMusicaActual = --opcio;
    //cout << endl << endl << m_arxiusMusica[opcio];

    return "data\\Audio\\" + m_arxiusMusica[m_indexMusicaActual];
}


void Partida::llistarArxius()
{
    //string carpeta = "C:\\Users\\alici\\source\\repos\\projecte MP\\intro_llibreria_grafica\\intro_llibreria_grafica_estudiants\\1. Resources\\data\\Audio";
    string carpeta = "..\\1. Resources\\data\\Audio";

    string rutaBusqueda = carpeta + "\\*";
    WIN32_FIND_DATAA arxiuTrobat;
    HANDLE handle = FindFirstFileA(rutaBusqueda.c_str(), &arxiuTrobat);

    if (handle == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error al obrir la carpeta: " << carpeta << std::endl;
        return;
    }

    m_numArxius = 0;
    do
    {
        const std::string arxiu = arxiuTrobat.cFileName;
        if (arxiu != "." && arxiu != ".." && m_numArxius < MAX_ARXIUS)
        {
            m_arxiusMusica[m_numArxius] = arxiu;

            if (arxiu == "Tetris.mp3")
            {
                m_indexMusicaActual = m_numArxius;
            }
            ++m_numArxius;
        }

    } while (FindNextFileA(handle, &arxiuTrobat) != 0);

    FindClose(handle);
}

void Partida::reproduirSeguentCanco()
{
    m_indexMusicaActual = (m_indexMusicaActual + 1) % m_numArxius; // Pasar a la canco de la llista

    reprodueixMusica("data\\Audio\\" + m_arxiusMusica[m_indexMusicaActual]);
}
