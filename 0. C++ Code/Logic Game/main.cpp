//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"


//eliminar
#include "GraphicManager.h"


int main(int argc, const char* argv[])
{
    int mode = 0;
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
    
    if (estaJugant)
    {
        //Instruccions necesaries per poder incloure la llibreria i que trobi el main
        SDL_SetMainReady();
        SDL_Init(SDL_INIT_VIDEO);

        //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
        Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
        //Mostrem la finestra grafica
        pantalla.show();

        Partida game;

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;

        //game.figuraAleatoria();
        string fitxerInicial = "fitxerInicial.txt";
        string fitxerFigures = "fitxerFigures.txt";
        string fitxerMov = "fitxerMov.txt";
        game.inicialitza(mode, fitxerInicial,fitxerFigures,fitxerMov);

        do
        {
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

            // Captura tots els events de ratolí i teclat de l'ultim cicle
            pantalla.processEvents();

            game.actualitza(mode, deltaTime);

            // Actualitza la pantalla
            pantalla.update();

        } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
        // Sortim del bucle si pressionem ESC

        game.escriuPuntuacio("puntuacions.txt");
        //Instruccio necesaria per alliberar els recursos de la llibreria 
        SDL_Quit();
    }
    return 0;
}

