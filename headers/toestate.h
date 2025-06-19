#pragma once

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
    int cursor_pos = 4;

  public:
    Toestate();

    void reset_game_board();

    const Player& get_active_player() const;
    const Player& get_game_winner() const;
    const int& get_cursor_position() const;
    const vector<Player>& get_board() const;

    void move_cursor_up();
    void move_cursor_down();
    void move_cursor_left();
    void move_cursor_right();

    void put_player_mark();
    void toggle_active_player();

    void run_game_winner_check();
    bool board_is_fully_played() const;
};
