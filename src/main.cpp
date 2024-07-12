#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include "config.h"
#include "calculate.h"
#include <thread>
#include <chrono>
// std::this_thread::sleep_for(std::chrono::milliseconds(50)); spát 50ms
// Funkce pro vykreslení textu
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 255, 255, 255}; // Bílá barva
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = textWidth;
    dst.h = textHeight;

    SDL_RenderCopy(renderer, textTexture, NULL, &dst);
    SDL_DestroyTexture(textTexture);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Calculate", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Nastavení barvy pozadí na #1C4F00
    SDL_SetRenderDrawColor(ren, 28, 79, 0, 255);
    SDL_RenderClear(ren);

    // Načtení fontu z instalační cesty
    std::string fontPath = std::string(INSTALL_PREFIX) + "/share/fonts/truetype/JosefinSans-Light.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Vykreslení úvodního textu
    renderText(ren, font, "Zadejte cisla cast a celkem:", 50, 50);

    // Povolení textového vstupu
    SDL_StartTextInput();

    // Vytvoření textového pole pro vstup uživatele
    std::string inputText = "";
    bool isInputChyb = true; // Zda se jedná o vstup pro chyb (true) nebo celkem (false)
    int chyb = 0; // Uchování hodnoty chyb pro pozdější použití
    int celkem = 0; // Uchování hodnoty celkem pro pozdější použití
    int procenta_val = 0; // Uchování hodnoty procent

    SDL_Event e;
    bool quit = false;
    bool displayResult = false; // Indikátor, zda se má zobrazit výsledek

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_TEXTINPUT) {
                inputText += e.text.text; // Přidá text z události do vstupního textu
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (!displayResult) {
                        if (isInputChyb) {
                            std::istringstream iss(inputText);
                            if (iss >> chyb) {
                                std::cout << "chyb = " << chyb << std::endl;
                            } else {
                                std::cerr << "Neplatny vstup pro cast" << std::endl;
                            }
                            inputText = "";
                            isInputChyb = false;
                            SDL_RenderClear(ren); // Vymazání obrazovky
                            SDL_SetRenderDrawColor(ren, 28, 79, 0, 255); // Opětovné nastavení barvy pozadí
                            renderText(ren, font, "Zadejte celkem:", 50, 100); // Zobrazí výzvu pro celkem
                        } else {
                            std::istringstream iss(inputText);
                            if (iss >> celkem) {
                                std::cout << "celkem = " << celkem << std::endl;
                                procenta_val = procenta(chyb, celkem);
                                std::cout << "Procenta(chyb, celkem) = " << procenta_val << "%" << std::endl;

                                std::ostringstream oss;
                                oss << "Procenta(chyb, celkem) = " << procenta_val << "%";
                                SDL_RenderClear(ren); // Vymazání obrazovky
                                SDL_SetRenderDrawColor(ren, 28, 79, 0, 255); // Opětovné nastavení barvy pozadí
                                renderText(ren, font, oss.str(), 50, 150); // Zobrazí výsledek v textovém poli

                                // Přejde do režimu zobrazení výsledku
                                displayResult = true;
                            } else {
                                std::cerr << "Neplatny vstup pro celkem" << std::endl;
                            }
                        }
                    } else {
                        // Uživatel stiskne Enter pro ukončení
                        quit = true;
                    }
                } else if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                    inputText.pop_back(); // Odstraní poslední znak
                }
            }
        }

        // Aktualizace obrazovky
        SDL_RenderPresent(ren);
    }

    // Uvolnění prostředků
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

