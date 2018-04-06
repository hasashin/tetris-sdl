#ifndef TETRIS_SDL_FONTS_H
#define TETRIS_SDL_FONTS_H

#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>

class font {
    std::string name;
    TTF_Font *data;

    friend class fontsContainer;

public:
    font(const std::string &name_, const char *filename, const int fontSize) : name(name_) {
        data = TTF_OpenFont(filename, fontSize);
    }

    ~font() {}

    TTF_Font *raw() {
        return data;
    }
};

class fontsContainer {
    std::vector<font *> data;
public:

    void add(const std::string &name, const char *filename, const int fontSize) {
        data.emplace_back(new font(name, filename, fontSize));
    }

    font *operator[](int index) {
        if (index < data.size()) return data[index];
        return nullptr;
    }

    font *operator[](const std::string &name) {
        for (auto &elem:data) {
            if (elem->name == name) return elem;
        }
        return nullptr;
    }
};

#endif //TETRIS_SDL_FONTS_H
