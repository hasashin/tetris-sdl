#include <SDL2/SDL.h>
#include <control.h>
#include <game.h>
#ifdef _WIN32
#include <ctime>
#endif
void init_all() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    TTF_Init();
    global::close = false;
    global::readSettings();
}

void addFonts(){
    global::fonts.add("default",(global::programDir+"fonts/dflt.ttf").c_str(),20);
    global::fonts.add("menu15",(global::programDir+"fonts/menu.ttf").c_str(),15);
    global::fonts.add("title",(global::programDir+"fonts/title.ttf").c_str(),300);
    global::fonts.add("menu50",(global::programDir+"fonts/menu.ttf").c_str(),50);
    global::fonts.add("8-bit15",(global::programDir+"fonts/8bit.ttf").c_str(),15);
    global::fonts.add("8-bit50",(global::programDir+"fonts/8bit.ttf").c_str(),50);
}
int main(int argc, char *args[]) {
#ifdef _WIN32
    srand(time(0));
#endif
    init_all();
    addFonts();

    game mainGame;
    while(!global::close){
        mainGame();
    }
    TTF_Quit();
    SDL_Quit();
    return 0;

}