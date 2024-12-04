#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "config.h"
#include "calculate.h"

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

// Globální proměnné pro komunikaci mezi vlákny
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
bool processed = false;
int chyb = 0;
int celkem = 0;
int procenta_val = 0;
std::string inputText = "";
bool isInputChyb = true;
bool displayResult = false;
bool quit = false;

void calculatePercentage() {
    while (!quit) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return ready || quit; });

        if (quit) break;

        // Provedení výpočtu
        procenta_val = procenta(chyb, celkem);

        processed = true;
        ready = false;
        cv.notify_one();
    }
}

void renderUI(SDL_Renderer* ren, TTF_Font* font) {
    SDL_Event e;
    
    while (!quit) {
        std::unique_lock<std::mutex> lock(mtx);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                cv.notify_one();
                break;
            } else if (e.type == SDL_TEXTINPUT) {
                inputText += e.text.text;
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
                        } else {
                            std::istringstream iss(inputText);
                            if (iss >> celkem) {
                                std::cout << "celkem = " << celkem << std::endl;

                                ready = true;
                                cv.notify_one();

                                cv.wait(lock, [] { return processed; });

                                displayResult = true;
                            } else {
                                std::cerr << "Neplatny vstup pro celkem" << std::endl;
                            }
                        }
                    } else {
                        quit = true;
                        cv.notify_one();
                    }
                } else if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                    inputText.pop_back();
                }
            }
        }

        // Vykreslení
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 28, 79, 0, 255);

        if (!displayResult) {
            renderText(ren, font, "Zadejte cisla cast a celkem:", 50, 50);
            if (isInputChyb) {
                renderText(ren, font, "Cast: " + inputText, 50, 100);
            } else {
                renderText(ren, font, "Celkem: " + inputText, 50, 100);
            }
        } else {
            std::ostringstream oss;
            oss << "Procenta(chyb, celkem) = " << procenta_val << "%";
            renderText(ren, font, oss.str(), 50, 150);
        }

        SDL_RenderPresent(ren);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
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

    std::thread calcThread(calculatePercentage);

    renderUI(ren, font);

    calcThread.join();

    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
