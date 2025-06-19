#include <vector>

using namespace std;

enum class Player {
  None,
  Cross,
  Circle,
};

bool has_value(Player p);
tuple<bool, Player> is_same_player_and_winner_is(vector<Player>);
