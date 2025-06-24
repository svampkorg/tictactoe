#include "toetype.h"
#include <algorithm>

using namespace std;

bool has_value(Player p) {

  if (p == Player::None)
    return false;

  return true;
}

tuple<bool, Player> get_game_status_from_combination(vector<Player> board_row) {

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
