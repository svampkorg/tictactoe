#include "toestate.h"

using namespace std;

int main() {

  // Element document = hbox({
  //     text("left") | border,
  //     text("middle") | border | flex,
  //     text("right") | border,
  // });

  auto state = Toestate();

  state.draw_board();

  return EXIT_SUCCESS;
}
