#include <gtest/gtest.h>
#include "InputStateManager.h"

TEST(InputStateManagerTest, InitialStateIsDefault)
{
    InputStateManager manager;
    ASSERT_EQ(manager.getCurrentState(), "Default");
}

TEST(InputStateManagerTest, SetStateChangesCurrentState)
{
    InputStateManager manager;
    manager.setState("Menu");
    ASSERT_EQ(manager.getCurrentState(), "Menu");
}

TEST(InputStateManagerTest, UpdateFromEventTracksKeyStates)
{
    InputStateManager manager;
    ASSERT_FALSE(manager.isKeyPressed(Key::A));

    manager.updateFromEvent({InputEventType::KeyPressed, {.key = {Key::A, Modifier::None}}});
    ASSERT_TRUE(manager.isKeyPressed(Key::A));

    manager.updateFromEvent({InputEventType::KeyReleased, {.key = {Key::A, Modifier::None}}});
    ASSERT_FALSE(manager.isKeyPressed(Key::A));
}

TEST(InputStateManagerTest, UpdateFromEventTracksMouseButtonStates)
{
    InputStateManager manager;
    ASSERT_FALSE(manager.isMouseButtonPressed(MouseButton::Left));

    manager.updateFromEvent({InputEventType::MouseButtonPressed, {.mouseButton = {MouseButton::Left, Modifier::None, 0, 0}}});
    ASSERT_TRUE(manager.isMouseButtonPressed(MouseButton::Left));

    manager.updateFromEvent({InputEventType::MouseButtonReleased, {.mouseButton = {MouseButton::Left, Modifier::None, 0, 0}}});
    ASSERT_FALSE(manager.isMouseButtonPressed(MouseButton::Left));
}

TEST(InputStateManagerTest, GetModifiersReturnsCorrectBitmask)
{
    InputStateManager manager;
    ASSERT_EQ(manager.getModifiers(), Modifier::None);

    // Нажимаем левый Shift
    manager.updateFromEvent({InputEventType::KeyPressed, {.key = {Key::LeftShift, Modifier::None}}});
    ASSERT_EQ(manager.getModifiers(), Modifier::LeftShift);

    // Нажимаем правый Ctrl
    manager.updateFromEvent({InputEventType::KeyPressed, {.key = {Key::RightCtrl, Modifier::None}}});
    ASSERT_EQ(manager.getModifiers(), Modifier::LeftShift | Modifier::RightCtrl);

    // Отпускаем левый Shift
    manager.updateFromEvent({InputEventType::KeyReleased, {.key = {Key::LeftShift, Modifier::None}}});
    ASSERT_EQ(manager.getModifiers(), Modifier::RightCtrl);

    // Отпускаем правый Ctrl
    manager.updateFromEvent({InputEventType::KeyReleased, {.key = {Key::RightCtrl, Modifier::None}}});
    ASSERT_EQ(manager.getModifiers(), Modifier::None);
}