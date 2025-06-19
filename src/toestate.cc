#include "../headers/toestate.h"
#include <algorithm>

Toestate::Toestate() : board(9) {}

void Toestate::new_board() {
  fill(board.begin(), board.end(), Player::None);
  player_active = Player::Cross;
  player_winner = Player::None;
}

const vector<Player>& Toestate::get_board() const {
  return board;
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

const Player& Toestate::get_player() const { return player_active; }
const Player& Toestate::get_winner() const { return player_winner; }
const int& Toestate::get_cursor_pos() const { return cursor_pos; }

bool Toestate::board_is_fully_played() const {

  return all_of(board.begin(), board.end(),
                [](const auto &element) { return element != Player::None; });

}

void Toestate::run_board_check() {

  auto get_is_same_mark_and_winning_player = [&](vector<int> combination) -> tuple<bool, Player> {
    auto game_status = get_game_status_from_combination(
        {board[combination[0]], board[combination[1]], board[combination[2]]});
    return game_status;
  };

  vector<vector<int>> board_win_combinations = {
      {0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7},
      {2, 4, 6}, {2, 5, 8}, {3, 4, 5}, {6, 7, 8},
  };

  bool is_same_player_mark_in_row = false;
  Player player_mark = Player::None;

  for (const auto &board_combination : board_win_combinations) {

    auto board_combination_status = get_is_same_mark_and_winning_player(board_combination);

    is_same_player_mark_in_row = get<0>(board_combination_status);
    player_mark = get<1>(board_combination_status);

    if (is_same_player_mark_in_row && player_mark != Player::None) {
      player_winner = player_mark;
      break;
    } else {
      is_same_player_mark_in_row = false;
      player_mark = Player::None;
    }
  }
}
