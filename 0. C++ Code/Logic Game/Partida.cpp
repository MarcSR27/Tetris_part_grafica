#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"



Partida::Partida()
{

    m_puntuacio = 0;
    m_nivell = 0;
    m_temps = 0;
    m_incrementVelocitat = 0;

    m_joc = Joc();
    m_partidaAcabada = false;

}

void Partida::inicialitza(int const mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (mode == 1) //mode test
    {
        //ACTUALITZA EL TAULER AL SEU ESTAT INICIAL

       m_joc.inicialitza(fitxerInicial);

        //GUARDA LES FIGURES QUE APAREIXERAN

        //GUARDA ELS MOVIMENTS QUE ES FARAN

    }
    else //mode normal
    {
        //INICIALITZA EL TAULER A BUIT
        m_joc = Joc();

        //GENERA ALEATORIAMENT UNA FIGURA
        int estat, columna;
        TipusFigura tipusFigura;

        tipusFigura = generarTipusFiguraAleatoria();
        columna = generarNumAleatori(0, MAX_COL);
        estat = generarNumAleatori(0, 4);

        m_joc.setFigura(columna, tipusFigura, estat);
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
        if (m_puntuacio >= m_nivell * 1000)
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
        columna = generarNumAleatori(0, MAX_COL);
        estat = generarNumAleatori(0, 4);

    } while (!m_joc.setFigura(columna, tipusFigura, estat));
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
    uniform_int_distribution<> distrib(static_cast<int>(TipusFigura::FIGURA_O), static_cast<int>(TipusFigura::FIGURA_S));
    int valorAleatorio = distrib(gen);

    return static_cast<TipusFigura>(valorAleatorio); //Pasar de int a Tipus Figura, que no deixaba retornar
}


void Partida::actualitza(int const mode, double deltaTime)
{
    int filesEliminades = 0;
    bool baixa = true;

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();

    //ACCIONS DE TECLAT
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

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();


    if (baixa)
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
    if (!m_partidaAcabada)
    {
        string msg = "Fila: " + to_string(m_joc.getFilaFigura()) + ", Columna: " + to_string(m_joc.getColFigura());
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

        string puntuacio = "Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 260 , POS_Y_TAULER - 80, 1.0, puntuacio);

        string nivell = "Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 260, POS_Y_TAULER - 110, 1.0, nivell);

    }
    else
    {
        string msg = "Puntuacio Final: " + to_string(m_puntuacio) + ", Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

        string escape = "Prem ESCAPE per sortir";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 30, 1.0, escape);
        
    }

    if (!baixa) //la figura s'ha posat al tauler
    {
        puntuacioINivell(filesEliminades);

        if (m_joc.getFilaFigura() == 0) // revisar, provisional
        {
            //s'ha acabat la partida
            m_partidaAcabada = true; //provisional

        }
        else //generem la seguent figura aleatoria
        {
            figuraAleatoria();
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
        while (!fitxer.eof())
        {
            cout << nomJugador << " " << puntuacio << endl;
            fitxer >> nomJugador >> puntuacio;
        }

    }
    fitxer.close();
}