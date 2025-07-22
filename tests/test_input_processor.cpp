#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "InputProcessor.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(InputProcessorTest, StateManagement)
{
    InputProcessor processor;
    ASSERT_EQ(processor.getCurrentState(), "Default");

    processor.setState("Menu");
    ASSERT_EQ(processor.getCurrentState(), "Menu");
}

TEST(InputProcessorTest, ExportConfiguration)
{
    InputProcessor processor;
    processor.defineAction("Jump", [] {});
    processor.defineAction("Fire", [] {});
    processor.registerKeyBinding("Default", "Jump", "Space", Modifier::None);
    processor.registerMouseButtonBinding("Default", "Fire", "Left", Modifier::LeftCtrl);

    json config = processor.exportConfiguration();

    ASSERT_TRUE(config.contains("Default"));
    const auto &defaultState = config["Default"];

    ASSERT_TRUE(defaultState.contains("keyboard_bindings"));
    const auto &kb = defaultState["keyboard_bindings"];
    ASSERT_TRUE(kb.contains("Jump"));
    ASSERT_EQ(kb["Jump"]["key"], "Space");
    ASSERT_TRUE(kb["Jump"]["modifiers"].empty());

    ASSERT_TRUE(defaultState.contains("mouse_bindings"));
    const auto &mb = defaultState["mouse_bindings"];
    ASSERT_TRUE(mb.contains("Fire"));
    ASSERT_EQ(mb["Fire"]["button"], "Left");
    ASSERT_THAT(mb["Fire"]["modifiers"], ::testing::ElementsAre("LeftCtrl"));
}

TEST(InputProcessorTest, ImportConfiguration)
{
    InputProcessor processor;
    bool jumpActionTriggered = false;
    processor.defineAction("Jump", [&]()
                           { jumpActionTriggered = true; });

    json config = {
        {"Default", {
                        {"keyboard_bindings", {{"Jump", {{"key", "A"}, {"modifiers", json::array({"LeftShift"})}}}}
                    }}}};

    processor.importConfiguration(config);

    // Проверяем, что привязка была создана, симулируя событие
    InputEvent event{InputEventType::KeyPressed, {.key = {Key::A, Modifier::LeftShift}}};
    processor.handleEvent(event);

    ASSERT_TRUE(jumpActionTriggered);
}