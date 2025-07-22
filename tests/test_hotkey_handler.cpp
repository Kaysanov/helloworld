#include <gtest/gtest.h>
#include "InputProcessor.h"
#include "InputStateManager.h"

TEST(HotkeyHandlerTest, TriggersActionOnKeyPress)
{
    InputProcessor processor;
    bool jumpActionTriggered = false;
    processor.defineAction("Jump", [&]()
                           { jumpActionTriggered = true; });
    processor.registerKeyBinding("Default", "Jump", "Space", Modifier::None);

    // Симулируем нажатие пробела
    InputEvent event{InputEventType::KeyPressed, {.key = {Key::Space, Modifier::None}}};
    processor.handleEvent(event);

    ASSERT_TRUE(jumpActionTriggered);
}

TEST(HotkeyHandlerTest, DoesNotTriggerActionInWrongState)
{
    InputProcessor processor;
    bool jumpActionTriggered = false;
    processor.defineAction("Jump", [&]()
                           { jumpActionTriggered = true; });
    processor.registerKeyBinding("InAir", "Jump", "Space", Modifier::None); // Действие только в состоянии "InAir"

    // Процессор находится в состоянии "Default"
    ASSERT_EQ(processor.getCurrentState(), "Default");

    InputEvent event{InputEventType::KeyPressed, {.key = {Key::Space, Modifier::None}}};
    processor.handleEvent(event);

    ASSERT_FALSE(jumpActionTriggered);
}

TEST(HotkeyHandlerTest, TriggersActionWithSpecificModifier)
{
    InputProcessor processor;
    bool saveActionTriggered = false;
    processor.defineAction("Save", [&]()
                           { saveActionTriggered = true; });
    processor.registerKeyBinding("Default", "Save", "S", Modifier::LeftCtrl);

    // Событие с правым Ctrl не должно сработать
    processor.handleEvent({InputEventType::KeyPressed, {.key = {Key::S, Modifier::RightCtrl}}});
    ASSERT_FALSE(saveActionTriggered);

    // Событие с левым Ctrl должно сработать
    processor.handleEvent({InputEventType::KeyPressed, {.key = {Key::S, Modifier::LeftCtrl}}});
    ASSERT_TRUE(saveActionTriggered);
}

TEST(HotkeyHandlerTest, TriggersActionOnKeyRelease)
{
    InputProcessor processor;
    bool throwGrenadeTriggered = false;
    processor.defineAction("Throw", [&]()
                           { throwGrenadeTriggered = true; });
    processor.registerKeyBinding("Default", "Throw", "G", Modifier::None, true); // onRelease = true

    processor.handleEvent({InputEventType::KeyPressed, {.key = {Key::G, Modifier::None}}});
    ASSERT_FALSE(throwGrenadeTriggered);

    processor.handleEvent({InputEventType::KeyReleased, {.key = {Key::G, Modifier::None}}});
    ASSERT_TRUE(throwGrenadeTriggered);
}