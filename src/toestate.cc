#include "../headers/toestate.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <sys/qos.h>

Toestate::Toestate() : board(9) {}
void Toestate::new_board() { fill(board.begin(), board.end(), nullopt); }
void Toestate::draw_board() {

  system("clear");

  using namespace ftxui;

  vector<Elements> lines;
  Elements line;

  cout << "Cursor pos is: " << cursor_pos << endl;

  for (int i = 0; i < board.size(); ++i) {
    const auto &place = board[i];

    string left = " ";
    string right = " ";
    string place_sign = to_string(i);

    if (place.has_value()) {
      if (place.value()) {
        place_sign = "O";
      } else {
        place_sign = "X";
      }
    } else {
      place_sign = " ";
    }

    auto board_place = [&]() {
      auto content = vbox({
                         hbox({text(left), text(place_sign), text(right)}),
                     }) |
                     border;
      if (i == cursor_pos) {
        return content | color(Color::Red);
      } else {
        return content | color(Color::Green);
      }
    };

    line.push_back(board_place());

    switch (i) {
    case 2:
      lines.push_back(line);
      line.clear();
      break;
    case 5:
      lines.push_back(line);
      line.clear();
      break;
    case 8:
      lines.push_back(line);
      line.clear();
      break;
    }
  }

  // auto summary = [&] {
  //   auto content = vbox({
  //       hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
  //       hbox({text(L"- active: "), text(L"2") | bold}) |
  //       color(Color::RedLight), hbox({text(L"- queue:  "), text(L"9") |
  //       bold}) | color(Color::Red),
  //   });
  //   return window(text(L" Summary "), content);
  // };

  Element document = window(text("Board"), gridbox(lines));

  document = document | size(WIDTH, ftxui::EQUAL, 15);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  cout << screen.ToString() << '\0' << endl;

  // for (int i = 0; i < board.size(); ++i) {
  //   const auto &place = board[i];
  //
  //   string left = "[";
  //   string right = "]";
  //
  //   if (i == cursor_pos) {
  //     left = "(";
  //     right = ")";
  //   }
  //
  //   sstream.clear();
  //
  //   if (i % 3 == 0) {
  //     sstream << endl;
  //   }
  //
  //   if (place == true) {
  //     sstream << left << "o" << right;
  //   } else if (place == false) {
  //     sstream << left << "x" << right;
  //   } else {
  //     sstream << left << i << right;
  //   }
  // }
  //
  // sstream << endl;
  //
  // cout << sstream.str();
  // cout << endl;
}

void Toestate::move_cursor_up() {
  if (cursor_pos - 3 >= 0) {
    cursor_pos -= 3;
  }
}

void Toestate::move_cursor_down() {
  if (cursor_pos + 3 <= 8) {
    cursor_pos += 3;
  }
}

void Toestate::move_cursor_left() {
  if (cursor_pos % 3 != 0) {
    cursor_pos -= 1;
  }
}

void Toestate::move_cursor_right() {
  if (cursor_pos % 3 != 2) {
    cursor_pos += 1;
  }
}

void Toestate::put_x() { board[cursor_pos] = true; }

void Toestate::put_o() { board[cursor_pos] = false; }

void Toestate::put_nullopt() { board[cursor_pos] = nullopt; }

void Toestate::toggle_player() { player = !player; }
