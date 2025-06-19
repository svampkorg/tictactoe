#pragma once

#include "toestate.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

struct UiElements {
    const static ftxui::Element board_element(const Toestate &state);
    const static ftxui::Element winner_element(const Toestate &state);
    const static ftxui::Element player_element(const Toestate &state);
    const static ftxui::Element instructions_element(const Toestate &state);
};
