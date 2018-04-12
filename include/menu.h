#ifndef TETRIS_SDL_MENULOGIC_H
#define TETRIS_SDL_MENULOGIC_H

#include <iostream>
#include <vector>

struct menuElement {
    int id;
    std::string data;


    menuElement(int id_, const std::string &data_) : id(id_), data(data_) {}
};

class menu : public object {
    std::vector<menuElement> elements;

    SDL_Window *window;

    friend class menuEvent;

    void keyboardInputControl(SDL_Scancode scancode) override {
        switch (scancode) {
            case SDL_SCANCODE_UP:
                global::menuptr->toggle(-1);
                break;
            case SDL_SCANCODE_DOWN:
                global::menuptr->toggle(1);
                break;
            case SDL_SCANCODE_RETURN:
                global::menuptr->doElementAction(window);
                break;
            case SDL_SCANCODE_ESCAPE:
                global::menuptr->toggle(INT32_MIN);
                global::menuptr->doElementAction(window);
            default:
                break;
        }
    }

    void generateMainMenu() {
        elements.emplace_back(0, "Nowa Gra");
        elements.emplace_back(1, "Ustawienia");
        elements.emplace_back(2, "Zakończ");
        activeElement = elements.begin();
    }

    void generateSettingsMenu(bool reset) {
        {
            std::string val = "Dźwięki:\t\t";
            val.append(global::enableSounds ? "Tak" : "Nie");
            elements.emplace_back(3, val);
        }
        {
            std::string val = "Muzyka:\t\t";
            val.append(global::enableMusic ? "Tak" : "Nie");
            elements.emplace_back(4, val);
        }
        {
            std::string val = "Pełny ekran:\t\t";
            val.append(global::fullscreen ? "Tak" : "Nie");
            elements.emplace_back(5, val);
        }
        elements.emplace_back(6, "Powrót");
        if (reset) activeElement = elements.begin();
    }

    void generateResolutionMenu() {}

    void generateMusicMenu() {}

    SDL_Renderer *rend = nullptr;

    std::vector<menuElement>::iterator activeElement;

    enum menuType {
        MT_MAIN,
        MT_SETTINGS,
        MT_RES,
        MT_MUSIC
    };

    void generateMenu(const menuType type, bool reset = true) {
        elements.clear();
        switch (type) {
            case MT_MAIN:
                generateMainMenu();
                break;
            case MT_SETTINGS:
                generateSettingsMenu(reset);
                break;
            case MT_RES:
                generateResolutionMenu();
                break;
            case MT_MUSIC:
                generateMusicMenu();
                break;
            default:
                break;
        }
    }

public:

    explicit menu(SDL_Renderer *&renderer, SDL_Window *window_) : rend(renderer), window(window_) {
        generateMenu(MT_MAIN);
    }

    void doElementAction(SDL_Window *window) {
        if (activeElement->id == 0) {
            global::state = global::PS_INGAME;
            return;
        }
        if (activeElement->id == 1) {
            generateMenu(MT_SETTINGS);
            return;
        }
        if (activeElement->id == 2) {
            global::close = true;
            return;
        }
        if (activeElement->id == 3) {
            global::enableSounds = !global::enableSounds;
            {
                global::writeSettings();
                generateMenu(MT_SETTINGS, false);
            }
            return;
        }
        if (activeElement->id == 4) {
            global::enableMusic = !global::enableMusic;
            {
                global::writeSettings();
                generateMenu(MT_SETTINGS, false);
            }
            return;
        }
        if (activeElement->id == 5) {
            global::fullscreen = !global::fullscreen;
            {
                global::writeSettings();
                if (global::fullscreen) {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                } else {
                    SDL_SetWindowFullscreen(window, 0);
                    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
                generateMenu(MT_SETTINGS, false);
            }
            return;
        }
        if (activeElement->id == 6) {
            generateMenu(MT_MAIN);
            return;
        }
    }

    void operator()() {
        int offset = 0, w, h, ratio;
        for (auto &elem:elements) {
            SDL_Texture *texture;
            SDL_Color color{155, 155, 155, 255};
            if (activeElement->id == elem.id) {
                color.r = 255;
                color.g = 255;
                color.b = 255;
            }
            texture = global::renderText(rend, elem.data, color, "menu50");
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            ratio = w / h;
            h = int(0.06 * global::SCREEN_H);
            w = h * ratio;
            global::drawScaledTexture(global::SCREEN_W / 2 - w / 2, global::SCREEN_H / 2 + offset * h, w, h, texture,
                                      rend);
            offset++;
            SDL_DestroyTexture(texture);
        }
    }

    void toggle(const int offset) {
        if (offset == INT32_MIN) {
            activeElement = elements.end() - 1;
        } else if (offset == INT32_MAX) {
            activeElement = elements.begin();
        } else if ((offset > 0 && activeElement != elements.end() - 1) ||
                   (offset < 0 && activeElement != elements.begin())) {
            activeElement = activeElement + offset;
        }
    }

};

#endif //TETRIS_SDL_MENULOGIC_H
