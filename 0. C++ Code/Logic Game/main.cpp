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

#include "./Tetris.h"
#include "./InfoJoc.h"

#include <thread>
#include <chrono> // per poder veure com es mouen les figures, unicament en el mode test
#include <cstdlib>


//
//#include "GraphicManager.h"


int main(int argc, const char* argv[])
{
    Tetris game;

    string partida;
    string figures;
    string moviments;

    string fitxerPuntuacions = "data\/Games\/puntuacions.txt";

    bool estaJugant = game.menuInicial(fitxerPuntuacions, partida,figures,moviments); 

    string fitxerInicial = "data\/Games\/" + partida;
    string fitxerFigures = "data\/Games\/" + figures;
    string fitxerMov = "data\/Games\/" + moviments;

    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    //if (estaJugant) // si mira puntuacions o surt, no esta jugant
    while (estaJugant)
    {
        //Instruccions necesaries per poder incloure la llibreria i que trobi el main
        SDL_SetMainReady();
        SDL_Init(SDL_INIT_VIDEO);

        //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
        
        //Mostrem la finestra grafica
        pantalla.show();

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;
        
        game.inicialitza(fitxerInicial, fitxerFigures, fitxerMov);

        do
        {
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

            // Captura tots els events de ratolí i teclat de l'ultim cicle
            pantalla.processEvents();

            game.juga(deltaTime);

            // Actualitza la pantalla
            pantalla.update();
            if (game.getMode() == 1)
            {
                this_thread::sleep_for(std::chrono::seconds(1)); // un segon per moviment
            }

        } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
        
        pantalla.close();
        if (game.finalPartida(fitxerPuntuacions))
        {
            //game = Tetris();
            system("cls");
            cout << flush;
            estaJugant = game.menuInicial(fitxerPuntuacions, partida, figures, moviments);

            fitxerInicial = "data\/Games\/" + partida;
            fitxerFigures = "data\/Games\/" + figures;
            fitxerMov = "data\/Games\/" + moviments;

        }
        else
        {
            estaJugant = false;
            
        }
        
        
       
        
    } //while (estaJugant);
    pantalla.~Screen();
    return 0;
}

