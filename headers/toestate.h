#pragma once

#include <sstream>
#include <vector>
#include <optional>

using namespace std;

class Toestate {
  private:
    vector<optional<bool>> board;
    bool player;
    stringstream sstream;
    int cursor_pos = 4;

  public:
    Toestate();

    void new_board();
    void draw_board();

    void move_cursor_up();
    void move_cursor_down();
    void move_cursor_left();
    void move_cursor_right();

    void put_x();
    void put_o();
    void put_nullopt();

    void toggle_player();
};
