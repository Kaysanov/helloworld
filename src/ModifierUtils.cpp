#include "ModifierUtils.h"

SDL_Keymod ModifierUtils::normalize(SDL_Keymod mods)
{
    SDL_Keymod normalized = SDL_KMOD_NONE;

    if (mods & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL | SDL_KMOD_CTRL))
    {
        normalized |= SDL_KMOD_CTRL;
    }
    if (mods & (SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT | SDL_KMOD_SHIFT))
    {
        normalized |= SDL_KMOD_SHIFT;
    }
    if (mods & (SDL_KMOD_LALT | SDL_KMOD_RALT | SDL_KMOD_ALT))
    {
        normalized |= SDL_KMOD_ALT;
    }
    if (mods & (SDL_KMOD_LGUI | SDL_KMOD_RGUI | SDL_KMOD_GUI))
    {
        normalized |= SDL_KMOD_GUI;
    }

    return normalized;
}

bool ModifierUtils::checkModifiers(SDL_Keymod required, SDL_Keymod current)
{
    return (required & current) == required;
}