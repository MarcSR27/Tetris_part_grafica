#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

#include <random> // llibreria per num aleatoris

Partida::Partida()
{
    m_temps = 0;
    for (int i = 0; i < MIDA; i++)
        for (int j = 0; j < MIDA; j++)
            m_forma[i][j] = NO_COLOR;
    m_forma[0][0] = COLOR_BLAUFOSC;
    m_forma[1][0] = COLOR_BLAUFOSC;
    m_forma[1][1] = COLOR_BLAUFOSC;
    m_forma[1][2] = COLOR_BLAUFOSC;
    m_fila = 1;
    m_columna = 5;
}

int generarPosicioAleatoria()  // genera posicio aleatoria quan baixa la figura
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, N_COL_TAULER); //genera posicio random entre columnes 1 i ultima
    return distrib(gen);
}

void Partida::actualitza(double deltaTime)
{
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


    do
    {
        // Dibuja el fondo y el tablero
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

        // Crea el mensaje y lo dibuja en la pantalla
        string msg = "Fila: " + to_string(m_fila) + ", Columna: " + to_string(m_columna);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

        string tiempo = "Tiempo: " + to_string(deltaTime);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 100, 1.0, tiempo);

        // Dibuja un cuadrado en la posición actual
        GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + (m_columna * MIDA_QUADRAT), POS_Y_TAULER + ((m_fila - 1) * MIDA_QUADRAT), false);

        // Actualiza el tiempo y la fila
        m_temps += deltaTime;
        if (m_temps > 0.5)
        {
            if (m_fila < N_FILES_TAULER)
                m_fila++;
            m_temps = 0.0;
        }

        // Dibuja otro cuadrado verde en la nueva posición
        GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + (m_columna * MIDA_QUADRAT), POS_Y_TAULER + ((m_fila - 1) * MIDA_QUADRAT), false);

        // Maneja la entrada del teclado
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
        if (Keyboard_GetKeyTrg(KEYBOARD_R))
        {
            m_fila = 1;
            m_columna = generarPosicioAleatoria();
        }

    } while (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)); // !! No acabado, mejor no pulsar aun.




    // TODO 4: Imprimir text per pantalla
    //------------------------------------------
    // TODO 4.1: Mostrar la posició actual del quadrat a dalt del tauler





    //TODO 5: Mostrar l’estat inicial del joc amb el tauler i la figura inicialitzats del fitxer        
    //-----------------------------------------




}


