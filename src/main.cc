#include "ftxui/component/event.hpp"
#include "toestate.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

int main() {

  using namespace ftxui;
  auto state = Toestate();

  state.new_board();

  auto document = state.get_board();
  auto screen = ScreenInteractive::TerminalOutput();
  auto renderer = Renderer([&] { return document; });

  system("clear");

  auto component = CatchEvent(renderer, [&](Event event) {
    auto character = event.character().front();

    switch (character) {
    case 'q':
      screen.Exit();
      return true;
    case 'h':
      state.move_cursor_left();
      break;
    case 'j':
      state.move_cursor_down();
      break;
    case 'k':
      state.move_cursor_up();
      break;
    case 'l':
      state.move_cursor_right();
      break;
    case ' ':
      state.put_player_mark();
      state.toggle_player();
      break;
    default:
      if (event == Event::Return) {
        state.new_board();
      }
      break;
    }
    system("clear");

    state.check_board();

    const auto winner = state.get_winner();
    const auto board_full = state.board_is_fully_played();

    if (winner == Player::None && !board_full) {
      document = state.get_board();
    } else {
      document = state.declare_winner();
      state.new_board();
    }

    return false;
  });

  screen.Loop(component);

  return EXIT_SUCCESS;
}
