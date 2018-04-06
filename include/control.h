#ifndef TETRIS_SDL_CONTROL_H
#define TETRIS_SDL_CONTROL_H

#include <random>
#include <fonts.h>

class eventable;

//TODO: make virtual method callEvent or similar.

class menu;

class playground;

class game;

namespace global {
    enum programState {
        PS_MENU,
        PS_INGAME,
        PS_GAMEOVER,
        PS_PAUSE
    };
    programState state = PS_MENU;
    int SCREEN_W = 800, SCREEN_H = 600;
    bool close;
    bool enableMusic;
    bool enableSounds;
    bool fullscreen;

    fontsContainer fonts;
    std::string programDir(SDL_GetBasePath());

    menu *menuptr;
    game *gameptr;
    playground *playgroundptr;


    SDL_Texture *renderText(SDL_Renderer *rend, const std::string &text, SDL_Color color, const std::string &fontName) {
        {
            SDL_Surface *surf = TTF_RenderUTF8_Blended(global::fonts[fontName]->raw(), text.c_str(), color);
            SDL_Texture *renderedText = SDL_CreateTextureFromSurface(rend, surf);
            SDL_FreeSurface(surf);
            return renderedText;
        }
    }

    void drawTexture(int x, int y, SDL_Texture *texture, SDL_Renderer *rend) {
        SDL_Rect destRect;
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        destRect.x = x;
        destRect.y = y;
        destRect.h = h;
        destRect.w = w;
        SDL_RenderCopy(rend, texture, nullptr, &destRect);
    }

    void drawScaledTexture(int x, int y, int w, int h, SDL_Texture *texture, SDL_Renderer *rend) {
        SDL_Rect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.h = h;
        destRect.w = w;
        SDL_RenderCopy(rend, texture, nullptr, &destRect);
    }

    void writeSettings(){
        SDL_RWops* rw = SDL_RWFromFile((global::programDir + "config/docfig.dat").c_str(),"wb");
        SDL_RWwrite(rw,&enableSounds,sizeof(enableSounds),1);
        SDL_RWwrite(rw,&enableMusic,sizeof(enableMusic),1);
        SDL_RWwrite(rw,&fullscreen,sizeof(enableMusic),1);
        SDL_RWclose(rw);
    }
    void readSettings(){
        SDL_RWops* rw = SDL_RWFromFile((global::programDir + "config/docfig.dat").c_str(),"rb");
        SDL_RWread(rw,&enableSounds,sizeof(enableSounds),1);
        SDL_RWread(rw,&enableMusic,sizeof(enableMusic),1);
        SDL_RWread(rw,&fullscreen,sizeof(enableMusic),1);
        SDL_RWclose(rw);
    }

#ifdef _WIN32
    int random(int min = 0,int max = 100){
        return rand()%(max+1) + min;
    }
#else
    int random(int min = 0, int max = 100) {
        std::random_device rd;
        static std::default_random_engine e(rd());
        std::uniform_int_distribution<int> d(min, max);
        return d(e);
    }
#endif

}

class event{
    menu* mptr;
public:
    int executeEvents(SDL_Scancode& scode){
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    global::close = true;
                    return 1;
                case SDL_KEYDOWN:
                    scode=e.key.keysym.scancode;
                    return 2;
                default:
                    return 0;
            }
        }
        return -1;
    }

};

#endif //TETRIS_SDL_CONTROL_H
