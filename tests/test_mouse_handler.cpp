#include <gtest/gtest.h>
#include "InputProcessor.h"
#include "InputStateManager.h"

TEST(MouseHandlerTest, TriggersActionOnButtonPress)
{
    InputProcessor processor;
    bool fireActionTriggered = false;
    processor.defineAction("Fire", [&]()
                           { fireActionTriggered = true; });
    processor.registerMouseButtonBinding("Default", "Fire", "Left", Modifier::None);

    InputEvent event{InputEventType::MouseButtonPressed, {.mouseButton = {MouseButton::Left, Modifier::None, 100, 100}}};
    processor.handleEvent(event);

    ASSERT_TRUE(fireActionTriggered);
}

TEST(MouseHandlerTest, TriggersCallbackOnMouseMove)
{
    InputProcessor processor;
    bool callbackTriggered = false;
    int mouseX = 0, mouseY = 0;

    processor.registerMouseMoveCallback("Default", [&](int x, int y)
                                        {
        callbackTriggered = true;
        mouseX = x;
        mouseY = y; });

    InputEvent event{InputEventType::MouseMoved, {.mouseMove = {123, 456}}};
    processor.handleEvent(event);

    ASSERT_TRUE(callbackTriggered);
    ASSERT_EQ(mouseX, 123);
    ASSERT_EQ(mouseY, 456);
}

TEST(MouseHandlerTest, DoesNotTriggerCallbackInWrongState)
{
    InputProcessor processor;
    bool callbackTriggered = false;

    processor.registerMouseMoveCallback("Menu", [&](int, int)
                                        { callbackTriggered = true; });

    ASSERT_EQ(processor.getCurrentState(), "Default");
    processor.handleEvent({InputEventType::MouseMoved, {.mouseMove = {123, 456}}});
    ASSERT_FALSE(callbackTriggered);
}

TEST(MouseHandlerTest, TriggersCallbackOnMouseWheel)
{
    InputProcessor processor;
    bool callbackTriggered = false;
    float wheelX = 0.0f, wheelY = 0.0f;

    processor.registerMouseWheelCallback("Default", [&](float x, float y)
                                         {
        callbackTriggered = true;
        wheelX = x;
        wheelY = y; });

    processor.handleEvent({InputEventType::MouseWheel, {.mouseWheel = {1.0f, -1.0f}}});
    ASSERT_TRUE(callbackTriggered);
    ASSERT_EQ(wheelX, 1.0f);
    ASSERT_EQ(wheelY, -1.0f);
}