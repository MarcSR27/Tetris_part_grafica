#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

#include <random> // llibreria per num aleatoris

Partida::Partida()
{
    /*m_temps = 0;
    for (int i = 0; i < MIDA; i++)
        for (int j = 0; j < MIDA; j++)
            m_forma[i][j] = NO_COLOR;
    m_forma[0][0] = COLOR_BLAUFOSC;
    m_forma[1][0] = COLOR_BLAUFOSC;
    m_forma[1][1] = COLOR_BLAUFOSC;
    m_forma[1][2] = COLOR_BLAUFOSC;
    m_fila = 1;
    m_columna = 5;*/
    
    /////
    m_puntuacio = 0;

    //m_figuraNova = NO_FIGURA;
    //m_estatFiguraNova = -1;
    m_nivell = 0;

    m_joc = Joc();

}

void Partida::inicialitza(int const mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (mode == 1) //mode test
    {
        //ACTUALITZA EL TAULER AL SEU ESTAT INICIAL
        //m_joc.inicialitza(fitxerInicial);

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

        //bool canvi = m_joc.setFigura(columna, tipusFigura, estat);
        m_joc.setFigura(columna, tipusFigura, estat);
    }

    m_nivell = 0;
    m_puntuacio = 0;
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

/*
void Partida::dibuixaFigura(Figura& figura)
{
    //Per poder fer servir les funcions de clase Figura
    const int(&formaFigura)[MAX_ALCADA][MAX_AMPLADA] = figura.getFormaFiguraActual();

    // Obtenir la posicio de la figura
    int filaInicial = m_fila - 1;
    int columnaInicial = m_columna;
    
    IMAGE_NAME bloc = GRAFIC_FONS;
    switch (figura.getColor())
    {
    case COLOR_GROC: bloc = GRAFIC_QUADRAT_GROC; break;
    case COLOR_BLAUCEL: bloc = GRAFIC_QUADRAT_BLAUCEL; break;
    case COLOR_MAGENTA: bloc = GRAFIC_QUADRAT_MAGENTA; break;
    case COLOR_TARONJA: bloc = GRAFIC_QUADRAT_TARONJA; break;
    case COLOR_BLAUFOSC: bloc = GRAFIC_QUADRAT_BLAUFOSC; break;
    case COLOR_VERMELL: bloc = GRAFIC_QUADRAT_VERMELL; break;
    case COLOR_VERD: bloc = GRAFIC_QUADRAT_VERD; break;
    }
    // Crea la figura
    for (int fila = 0; fila < MAX_ALCADA; fila++)
    {
        for (int columna = 0; columna < MAX_AMPLADA; columna++)
        {
            if (figura.getFormaFiguraActual()[fila][columna] != COLOR_NEGRE) // si es diferente de negre, hi ha que pintar aquell bloc
            {
                // Per reduir, indica la posicio per pantalla
                int x = POS_X_TAULER + (columnaInicial + columna) * MIDA_QUADRAT;
                int y = POS_Y_TAULER + (filaInicial + fila) * MIDA_QUADRAT;

                // Dibuixa la figura
                GraphicManager::getInstance()->drawSprite(bloc, x, y, false);
            }
        }
    }
}*/

/*
void Partida::movimentFigura(Figura& figura)
{
    const int(&formaFigura)[MAX_ALCADA][MAX_AMPLADA] = figura.getFormaFiguraActual();

    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
        if (m_columna < N_COL_TAULER and m_fila < N_FILES_TAULER)
            m_columna++;
    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        if (m_columna > 1 and m_fila < N_FILES_TAULER)
            m_columna--;
    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
        if (m_fila < N_FILES_TAULER)
            m_fila = N_FILES_TAULER;

    // Reinicia la posición si se presiona la tecla 'R'
    //Unicament per Provar
    if (Keyboard_GetKeyTrg(KEYBOARD_R))
    {
        m_fila = 1;
        m_columna = generarNumAleatori(1, N_COL_TAULER);

        m_figuraNova = generarFiguraAleatoria(FIGURA_O, FIGURA_S);
        m_estatFiguraNova = generarNumAleatori(0, 3);

        Figura figura(m_figuraNova, m_estatFiguraNova); // figura i estat
        dibuixaFigura(figura);
    }*





}*/

void Partida::actualitza(int const mode, double deltaTime) //!!!!NOTA - EL CODI ESTA AL FINAL DELS COMENTARIS
{
    /*// Dibuja el fondo y el tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    // Crea el mensaje y lo dibuja en la pantalla
    string msg = "Fila: " + to_string(m_fila) + ", Columna: " + to_string(m_columna);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

    string tiempo = "Tiempo: " + to_string(deltaTime);
    
    if (!m_figuraInicialGenerada)
    {
        m_figuraNova = generarFiguraAleatoria(FIGURA_O, FIGURA_S);
        m_estatFiguraNova = generarNumAleatori(0, 3);

        m_figuraInicialGenerada = true;
    }
    Figura figura(m_figuraNova, m_estatFiguraNova);
    dibuixaFigura(figura);

    // Actualiza el tiempo y la fila
    m_temps += deltaTime;
    if (m_temps > 0.5)
    {
        if (m_fila < N_FILES_TAULER)
            m_fila++;
        m_temps = 0.0;
    }
    movimentFigura(m_figura);
    

    /*
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 100, 1.0, tiempo);
    for (int i = 0; i < MIDA - 2; i++) {
        for (int j = 0; j < MIDA - 2; j++)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + ((m_columna + i) * MIDA_QUADRAT), POS_Y_TAULER + ((m_fila - 1 + j) * MIDA_QUADRAT), false);
        }
    }
   */

    

    //TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
    // 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit.
    //------------------------------------------------------------------

    //TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h"
    //TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY, centered);
    //	    Per començar podem cridar el drawSprite amb els params --> 
    //          (GRAFIC_FONS,0,0, false) i 
    //          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false)





    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i un quadrat groc a la posició (2,3) del tauler



    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i la figura representada a la matriu m_forma 
    // a la posició del tauler indicada per m_fila i m_columna




    //TODO 2: Interacció amb el teclat
    //------------------------------------------
    // TODO 2.1: Dibuixar dibuixar per pantalla un quadrat groc a la posicio indicada per m_fila i 
    // m_columna i que es vagi movent cap a la dreta cada cop que es prem la tecla de la fletxa dreta. 



    // TODO 2.2 Dibuixar a pantalla el gràfic amb el tauler i la figura representada a l’atribut m_forma
    // a la posició del tauler indicada per m_fila i m_columna. 
    // Moure la figura cap a la dreta o l’esquerra si es pressionen les tecles de les fletxes corresponents, 
    // comprovant que no ens passem dels limits del tauler. 



    //TODO 3: Introduir un temps d'espera
    //-----------------------------------
    // TODO 3.1: Dibuixar dibuixar per pantalla un quadrat groc a la posicio indicada per m_fila i 
    // m_columna. Fer que cada mig segon baixi una fila




    // TODO 3.2: Dibuixar per pantalla un quadrat groc a la posicio indicada per m_fila i  m_columna.
    // Moure el quadrat cap a la dreta o l’esquerra si es pressionen les tecles de les fletxes corresponents, 
    // comprovant que no ens passem dels limits del tauler.
    // Fer que cada segon baixi una fila, comprovant que no ens passem del limit inferior del tauler.





    // TODO 4: Imprimir text per pantalla
    //------------------------------------------
    // TODO 4.1: Mostrar la posició actual del quadrat a dalt del tauler





    //TODO 5: Mostrar l’estat inicial del joc amb el tauler i la figura inicialitzats del fitxer        
    //-----------------------------------------

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

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false); 
    m_joc.dibuixa();


    //BAIXAR FIGURA
    m_temps += deltaTime;
    if (m_temps > 0.5)
    {
        baixa = m_joc.baixaFigura(filesEliminades);
        if (!baixa)
        {
            //figuraAleatoria();
        }
        m_temps = 0.0;
    }

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa();


    //MOSTRAR TEXT
    string msg = "Fila: " + to_string(m_joc.getFilaFigura()) + ", Columna: " + to_string(m_joc.getColFigura());
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

    if (!baixa)
    {
        figuraAleatoria();
    }


}


