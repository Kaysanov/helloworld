#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

#include "IInputHandler.h"
#include "InputStateManager.h"
#include "HotkeyHandler.h"
#include "MouseHandler.h"

// Forward declaration for friend class
class ConfigManager;

// Forward declarations to break circular dependencies
//class HotkeyHandler;
//class MouseHandler;

class InputProcessor : public IInputHandler
{
public:
    using ActionMap = std::unordered_map<std::string, std::function<void()>>;

    InputProcessor();
    ~InputProcessor() = default;

    void handleEvent(const InputEvent &event) override;

    // --- Action Management ---
    void defineAction(const std::string& name, std::function<void()> callback);
    void defineActions(const ActionMap& actions);
    void triggerAction(const std::string& actionName);
    std::vector<std::string> getActionNames() const;

    // --- Binding Management (Facade) ---
    void registerKeyBinding(const std::string& state, const std::string& actionName, const std::string& keyName, uint16_t modifiers, bool onRelease = false);
    void registerMouseButtonBinding(const std::string& state, const std::string& actionName, const std::string& buttonName, uint16_t modifiers, bool onRelease = false);

    // --- State Management (Facade) ---
    void setState(const std::string& newState);
    const std::string& getCurrentState() const;

private:
    friend class ConfigManager; // Allow ConfigManager to access private handlers

    // Internal handler access
    HotkeyHandler& getHotkeyHandler() { return hotkeyHandler; }
    const HotkeyHandler& getHotkeyHandler() const { return hotkeyHandler; }
    MouseHandler& getMouseHandler() { return mouseHandler; }
    const MouseHandler& getMouseHandler() const { return mouseHandler; }
    InputStateManager &getStateManager() { return stateManager; }

    void addHandler(IInputHandler *handler);

    InputStateManager stateManager;
    ActionMap actionMap_;

    std::vector<IInputHandler *> handlers;
    HotkeyHandler hotkeyHandler;
    MouseHandler mouseHandler;
};
