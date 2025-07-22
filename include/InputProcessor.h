#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include <string_view>
#include <nlohmann/json_fwd.hpp>

#include "IInputHandler.h"
#include "InputStateManager.h"
#include "HotkeyHandler.h"
#include "MouseHandler.h"

// Forward declaration for friend class

class InputProcessor : public IInputHandler
{
public:
    using ActionMap = std::unordered_map<std::string, std::function<void()>>;

    InputProcessor();
    ~InputProcessor() = default;

    void handleEvent(const InputEvent &event) override;

    // --- Action Management ---
    void defineAction(std::string_view name, std::function<void()> callback);
    void defineActions(const ActionMap& actions);
    void triggerAction(const std::string& actionName);
    std::vector<std::string> getActionNames() const;

    // --- Binding Management (Facade) ---
    void registerKeyBinding(std::string_view state, std::string_view actionName, std::string_view keyName, uint16_t modifiers, bool onRelease = false);
    void registerMouseButtonBinding(std::string_view state, std::string_view actionName, std::string_view buttonName, uint16_t modifiers, bool onRelease = false);
    
    // --- Callback Management for Continuous Input ---
    void registerMouseMoveCallback(const std::string& state, std::function<void(int, int)> callback);
    void registerMouseWheelCallback(const std::string& state, std::function<void(float, float)> callback);

    // --- State Management (Facade) ---
    void setState(const std::string& newState);
    const std::string& getCurrentState() const;

    // --- Configuration Management ---
    nlohmann::json exportConfiguration() const;
    void importConfiguration(const nlohmann::json& config);

private:
    // Internal handler access
    const HotkeyHandler& getHotkeyHandler() const { return hotkeyHandler; }
    const MouseHandler& getMouseHandler() const { return mouseHandler; }
    InputStateManager &getStateManager() { return stateManager; }

    void addHandler(IInputHandler *handler);


    InputStateManager stateManager;
    ActionMap actionMap_;

    std::vector<IInputHandler *> handlers;
    HotkeyHandler hotkeyHandler;
    MouseHandler mouseHandler;
};
