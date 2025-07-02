#ifndef MODIFIERUTILS_H
#define MODIFIERUTILS_H

#include <SDL3/SDL.h>

class ModifierUtils
{
public:
    static SDL_Keymod normalize(SDL_Keymod mods);
    static bool checkModifiers(SDL_Keymod required, SDL_Keymod current);
};

#endif // MODIFIERUTILS_H