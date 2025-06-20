#include <vector>

using namespace std;

enum class Player {
  None,
  Cross,
  Circle,
};

bool has_value(Player p);
tuple<bool, Player> get_winner_from_combination(vector<Player>);
