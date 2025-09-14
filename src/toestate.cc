#include "../headers/toestate.h"
#include <tuple>
#include <functional>

Toestate::Toestate() : board(9) {

  reset_game_board();

}

void Toestate::reset_game_board() {

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

void Toestate::put_player_mark(OnMarkPlacedCallback on_mark_placed) {

  if (board[cursor_pos] == Player::None) {
    board[cursor_pos] = player_active;
    on_mark_placed();
  }

}

void Toestate::toggle_active_player() {

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

Player Toestate::get_active_player() const { return player_active; }
Player Toestate::get_game_winner() const { return player_winner; }
int Toestate::get_cursor_position() const { return cursor_pos; }

bool Toestate::board_is_fully_played() const {

  return all_of(board.begin(), board.end(),
                [](const auto &element) { return element != Player::None; });

}

tuple<bool, Player> Toestate::get_winner_from_combination(const vector<Player>& board_row) {

  Player player = board_row[0];
  auto begin = board_row.begin();
  auto end = board_row.end();

  if (any_of(begin, end,
             [](const auto &element) { return element == Player::None; })) {

    return {false, Player::None};

  } else {

    auto is_same = all_of(
        begin, end, [begin](const auto &element) { return element == *begin; });
    return {is_same, player};

  }
}

void Toestate::run_game_winner_check() {

  vector<vector<int>> board_win_combinations = {
      {0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7},
      {2, 4, 6}, {2, 5, 8}, {3, 4, 5}, {6, 7, 8},
  };

  for (const auto &board_combination : board_win_combinations) {

    auto board_combination_status = get_winner_from_combination(
        {board[board_combination[0]], board[board_combination[1]], board[board_combination[2]]});
    auto& [is_same_player_mark_in_row, player_mark] = board_combination_status;

    if (is_same_player_mark_in_row && player_mark != Player::None) {
      player_winner = player_mark;
      break;
    }
  }
}
