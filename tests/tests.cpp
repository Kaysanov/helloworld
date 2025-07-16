#include "InputStateManager.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fmt/format.h>

TEST(InputStateManagerTest, GetModifiers_DefaultState_NoModifiers)
{
    InputStateManager manager;
    uint16_t modifiers = manager.getModifiers();
    EXPECT_EQ(modifiers, 0);
}



TEST(InputStateManagerTest, GetModifiers_ShiftPressed_ShiftModifierSet)
{
    InputStateManager manager;
    InputEvent event{ InputEventType::KeyPressed, Key::LeftShift };
    manager.updateFromEvent(event);
    fmt::print("Modifiers: {}\n", manager.getModifiers());  
    EXPECT_TRUE(manager.isKeyPressed(Key::LeftShift)); 
    EXPECT_EQ(manager.getModifiers(), 4); // Shift — бит 3
}
/*
TEST(InputStateManagerTest, GetModifiers_CtrlAndAltPressed_ModifiersCombined)
{
    InputStateManager manager;
    
    InputEvent event1;
    event1.type = InputEventType::KeyPressed;
    event1.key = Key::Ctrl;
    event1.isPressed = true;
    manager.updateFromEvent(event1);
    
    InputEvent event2;
    event2.type = InputType::Key;
    event2.key = Key::Alt;
    event2.isPressed = true;
    manager.updateFromEvent(event2);
    
    uint16_t modifiers = manager.getModifiers();
    uint16_t expectedModifiers = 0;
    expectedModifiers |= (1 << 2); // Assume Ctrl is at position 2
    expectedModifiers |= (1 << 3); // Assume Alt is at position 3
    EXPECT_EQ(modifiers, expectedModifiers);
}
*/