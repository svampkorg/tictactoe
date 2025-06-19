#pragma once

#include <sstream>
#include <vector>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <sys/qos.h>
#include "toetype.h"

using namespace std;

class Toestate {
  private:
    vector<Player> board;
    Player player_active;
    Player player_winner;
    stringstream sstream;
    int cursor_pos = 4;
    void put_none();

  public:
    Toestate();

    void new_board();
    Player get_player();
    Player get_winner();

    ftxui::Element ftxui_get_board();
    ftxui::Element ftxui_declare_winner();
    ftxui::Element ftxui_active_player();
    ftxui::Element ftxui_instructions();

    void move_cursor_up();
    void move_cursor_down();
    void move_cursor_left();
    void move_cursor_right();

    void put_player_mark();
    void toggle_player();

    void check_board();
    bool board_is_fully_played();
};
