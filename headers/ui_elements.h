#pragma once

#include "toestate.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

struct UiElements {
    const static ftxui::Element build_board(const Toestate &state);
    const static ftxui::Element declare_winner(const Toestate &state);
    const static ftxui::Element active_player(const Toestate &state);
    const static ftxui::Element instructions(const Toestate &state);
};
