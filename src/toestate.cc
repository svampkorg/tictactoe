#include "../headers/toestate.h"
#include "ftxui/dom/elements.hpp"
#include <algorithm>

Toestate::Toestate() : board(9) {}
void Toestate::new_board() {
  fill(board.begin(), board.end(), Player::None);
  player_active = Player::Cross;
  player_winner = Player::None;
}
ftxui::Element Toestate::declare_winner() {
  using namespace ftxui;

  Element winner_text;
  switch (player_winner) {
  case Player::Circle:
    winner_text = text("0") | color(Color::Green);
    break;
  case Player::Cross:
    winner_text = text("X") | color(Color::Red);
    break;
  case Player::None:
    winner_text = text("It's a draw!") | color(Color::White);
    break;
  }

  auto winner = [&] {
    auto content = vbox({
        hbox({winner_text}) | color(Color::Purple),
    });
    return window(text(L" Winner is! "), content);
  };

  Element document =
      window(text("Board"), winner()) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 15);

  return document;
}
ftxui::Element Toestate::get_board() {

  using namespace ftxui;

  vector<Elements> lines;
  Elements line;

  for (int i = 0; i < board.size(); ++i) {

    string left = " ";
    string right = " ";

    auto board_place = [&](Player place) {
      Element player_mark_text = text(" ");

      switch (place) {
      case Player::Circle:
        player_mark_text = text("O") | color(Color::Green);
        break;
      case Player::Cross:
        player_mark_text = text("X") | color(Color::Red);
        break;
      default:
        break;
      }

      auto content = vbox({
                         hbox({text(left), player_mark_text, text(right)}),
                     }) |
                     border;

      if (i == cursor_pos) {
        switch (player_active) {
        case Player::Circle:
          return content | color(Color::Green);
        case Player::Cross:
          return content | color(Color::Red);
        default:
          break;
        }
      }
      return content | color(Color::White);
    };

    line.push_back(board_place(board[i]));

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

  Element document =
      window(text("Board"), gridbox(lines)) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 15);

  return document;
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

void Toestate::put_player_mark() {
  if (board[cursor_pos] == Player::None) {
    board[cursor_pos] = player_active;
  }
}

void Toestate::put_none() { board[cursor_pos] = Player::None; }

void Toestate::toggle_player() {
  switch (player_active) {
  case Player::Circle:
    player_active = Player::Cross;
    break;
  case Player::Cross:
    player_active = Player::Circle;
    break;
  default:
    break;
  }
}

Player Toestate::get_player() { return player_active; }
Player Toestate::get_winner() { return player_winner; }

bool Toestate::board_is_fully_played() {
  return all_of(board.begin(), board.end(),
                [](const auto &element) { return element != Player::None; });
}

void Toestate::check_board() {

  // lambda will return true if a, b and c are the same
  auto board_row_status = [&](vector<int> combination) -> tuple<bool, Player> {
    auto winner = is_same_player_and_winner_is(
        {board[combination[0]], board[combination[1]], board[combination[2]]});
    return winner;
  };

  vector<vector<int>> board_combinations = {
      {0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7},
      {2, 4, 6}, {2, 5, 8}, {3, 4, 5}, {6, 7, 8},
  };

  bool is_same_in_row = false;
  Player same_row_mark = Player::None;

  for (auto &combination : board_combinations) {

    auto board_combination_status = board_row_status(combination);

    is_same_in_row = get<0>(board_combination_status);
    same_row_mark = get<1>(board_combination_status);

    if (is_same_in_row && same_row_mark != Player::None) {
      player_winner = same_row_mark;
      break;
    } else {
      is_same_in_row = false;
      same_row_mark = Player::None;
    }
  }
}
