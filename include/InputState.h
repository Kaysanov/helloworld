/*Почему мы используем синглтон для InputState
Использование паттерна синглтон для InputState обусловлено несколькими ключевыми причинами:

1 Единственный источник истины
Состояние ввода (положение мыши, нажатые клавиши/кнопки) должно быть единым для всего приложения. Не должно быть нескольких экземпляров с разным состоянием.

2 Глобальная доступность
Множество систем (UI, игровая логика, камера) одновременно требуют доступа к состоянию ввода:

cpp
// Где-то в рендерере
if (InputState::get_instance().is_key_pressed(SDLK_F1)) show_debug_ui();

// Где-то в игровой логике
if (InputState::get_instance().is_mouse_button_pressed(SDL_BUTTON_LEFT)) attack();

3 Синхронизация состояния
События ввода обрабатываются в одном месте, гарантируя консистентность данных:

cpp
void InputState::handle_event(const SDL_Event* event) {
    // Централизованное обновление состояния
}

4 Эффективность
Избегаем:

Передачи экземпляра через все слои приложения

Избыточных вызовов SDL_GetMouseState()

Рассинхронизации между разными копиями состояния

5 Естественная модель работы
В SDL состояние ввода по своей природе глобально:

cpp
// Эти функции SDL по сути работают как синглтон
const Uint8* keystate = SDL_GetKeyboardState(nullptr);
Uint32 mouse = SDL_GetMouseState(nullptr, nullptr);



Альтернативы и почему они хуже

1 Передача по ссылке:

cpp
void Game::update(InputState& input) {
    if (input.is_key_pressed(SDLK_w)) // ...
}
Проблемы:

Загромождает сигнатуры методов

Усложняет архитектуру

Не решает проблему доступа из изолированных модулей

2 Глобальная переменная:

cpp
extern InputState g_input; // Плохая практика
Проблемы:

Нарушает инкапсуляцию

Сложности с порядком инициализации

Проблемы при многопоточности

3. Dependency Injection:

cpp
Engine engine(std::make_unique<InputState>());
Оправдано для тестирования, но избыточно для состояния ввода.

Когда стоит пересмотреть

Синглтон - оптимальное решение пока:
У вас одно окно приложения
Нет разделения на несколько независимых контекстов ввода
Не требуется параллельная обработка ввода в нескольких потоках
Если эти условия изменятся (например, при создании редактора с несколькими окнами), можно рассмотреть:

Контексты ввода (InputContext)

Внедрение зависимости с ограниченным временем жизни
Систему на основе компонентов
Но для 95% случаев игр и приложений с одним окном синглтон для состояния ввода - наиболее практичное и эффективное решение.
*/
#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL3/SDL.h>
#include <utility>

class InputState
{
public:
    static InputState &get_instance();

    void handle_event(const SDL_Event *event);
    void update();

    bool is_key_pressed(SDL_Keycode key) const;
    bool is_mouse_button_pressed(Uint8 button) const;
    std::pair<int, int> get_mouse_position() const;
    Uint32 get_mouse_buttons() const;
    void get_mouse_wheel(float &x, float &y) const;

    InputState(const InputState &) = delete;
    void operator=(const InputState &) = delete;

private:
    InputState() = default;

    int mouse_x = 0;
    int mouse_y = 0;
    Uint32 mouse_buttons = 0;
    float wheel_x = 0;
    float wheel_y = 0;
};

#endif