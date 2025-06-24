#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "toestate.h"
#include "ui_elements.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

int main() {

  using namespace ftxui;

  auto state = Toestate();
  state.reset_game_board();

  Element element_instructions = UiElements::instructions_element(state);

  Element element_board;
  Element element_active_player;
  Element element_screen;

  auto generate_screen_elements = [
    &element_board,
    &element_instructions,
    &element_active_player,
    &element_screen
  ](const Toestate &state) {

    const auto winner = state.get_game_winner();
    const auto board_full = state.board_is_fully_played();

    element_active_player = UiElements::player_element(state);

    if (winner == Player::None && !board_full) {

      element_board = UiElements::board_element(state);

      element_screen = vbox({
          element_active_player,
          hbox({
              element_board | flex,
          }),
          element_instructions,
      });
    } else {

      element_board = UiElements::winner_element(state);

      element_screen = vbox({
          hbox({
              element_board | flex,
          }),
          element_instructions,
      });
    }
  };

  generate_screen_elements(state);

  auto screen = ScreenInteractive::TerminalOutput();
  auto renderer = Renderer([&] { return element_screen; });

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
      state.toggle_active_player();
      state.run_game_winner_check();
      break;

    case 'N':
      state.reset_game_board();
      break;

    default:
      break;
    }

    system("clear");

    const auto winner = state.get_game_winner();
    const auto board_full = state.board_is_fully_played();

    if (!(winner == Player::None && !board_full)) {

      generate_screen_elements(state);
      state.reset_game_board();

    } else {

      generate_screen_elements(state);

    }

    return false;
  });

  screen.Loop(component);

  return EXIT_SUCCESS;
}
