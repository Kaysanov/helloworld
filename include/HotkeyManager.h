/*
Класс HotkeyManager
Назначение: Управление горячими клавишами и обработка событий ввода для SDL-приложений.
*/
/*
Ключевые особенности:
SOLID-архитектура:

InputState: Синглтон для хранения состояния ввода (мышь/клавиатура)

HotkeyRegistry: Управление регистрацией и обработкой горячих клавиш

MouseEventProcessor: Обработка событий мыши

HotkeyManager: Публичный интерфейс (фасад)

Поддерживаемые функции:

Регистрация комбинаций клавиш/мыши

Обработка движения мыши, колеса, кликов

Глобальная проверка состояния ввода

Игнорирование автоповтора клавиш

Паттерн проектирования:

Синглтон для InputState (единый источник истины)

Публичный фасад HotkeyManager

Пример использования:
cpp
HotkeyManager hm;

// Регистрация Ctrl+S
hm.register_hotkey(SDLK_s, SDL_KMOD_CTRL, []{
    std::cout << "Saving document..." << std::endl;
});

// Регистрация клика мыши
hm.register_click_callback(SDL_BUTTON_LEFT, []{
    auto [x, y] = HotkeyManager::get_mouse_position();
    std::cout << "Clicked at: " << x << ", " << y << std::endl;
});

// Основной цикл
while (running) {
    while (SDL_PollEvent(&event)) {
        hm.handle_event(&event);
    }
    hm.update();
    
    // Проверка состояния
    if (HotkeyManager::is_key_pressed(SDLK_SPACE)) {
        player.jump();
    }
}
Принцип работы:
Регистрация
Вызов register_hotkey(), register_click_callback() и т.д.

Обработка событий
Передача всех событий SDL в handle_event()

Обновление состояния
Вызов update() каждый кадр

Проверка состояния
Использование статических методов:

cpp
HotkeyManager::is_key_pressed(SDLK_a);
HotkeyManager::is_mouse_button_pressed(SDL_BUTTON_RIGHT);
HotkeyManager::get_mouse_position();
Почему синглтон для InputState?
Единственность состояния
Состояние ввода (координаты мыши, нажатые клавиши) должно быть единым для всего приложения.

Глобальная доступность
Множество модулей (UI, игровая логика) требуют доступа к состоянию ввода.

Синхронизация
Гарантирует консистентность данных между разными системами.

Эффективность
Избегает дублирования вызовов SDL API (SDL_GetKeyboardState и др.).

Ограничения:
Одно окно приложения
Для многоконных приложений требуется модификация.

Потокобезопасность
Не предназначен для многопоточного использования без доработки.

Рекомендации:
Порядок обработки
Всегда вызывать handle_event() до основной логики кадра.

Обновление состояния
Вызывать update() после обработки событий.

Комбинации клавиш
Использовать битовые флаги для модификаторов:

cpp
hm.register_hotkey(SDLK_DELETE, 
    SDL_KMOD_CTRL | SDL_KMOD_SHIFT, 
    [](){ ... });
https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png
Класс готов к интеграции в SDL-приложения. Для расширения функциональности см. исходный код компонентов.
*/
#ifndef HOTKEYMANAGER_H
#define HOTKEYMANAGER_H

#include "InputState.h"
#include "HotkeyRegistry.h"
#include "MouseEventProcessor.h"

class HotkeyManager
{
public:
    using Callback = HotkeyRegistry::Callback;
    using PositionCallback = MouseEventProcessor::PositionCallback;
    using WheelCallback = MouseEventProcessor::WheelCallback;

    void register_hotkey(SDL_Keycode key, SDL_Keymod modifiers, Callback callback);
    void register_mouse_hotkey(Uint8 button, SDL_Keymod modifiers, Callback callback);

    void register_motion_callback(PositionCallback callback);
    void register_wheel_callback(WheelCallback callback);
    void register_click_callback(Uint8 button, Callback callback);

    void update();
    void handle_event(const SDL_Event *event);

    // Статические методы делегируются InputState
    static bool is_key_pressed(SDL_Keycode key);
    static bool is_mouse_button_pressed(Uint8 button);
    static std::pair<int, int> get_mouse_position();

private:
    
    HotkeyRegistry hotkey_registry;
    MouseEventProcessor mouse_processor;

    static SDL_Keymod get_current_modifiers();
};

#endif