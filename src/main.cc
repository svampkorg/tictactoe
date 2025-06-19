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

  state.new_board();

  Element element_instructions = UiElements::instructions(state);

  Element element_board;
  Element element_active_player;
  Element screen_document;

  auto draw_screen_document = [&element_board, &element_instructions,
                               &element_active_player,
                               &screen_document](const Toestate &state) {
    const auto winner = state.get_winner();
    const auto board_full = state.board_is_fully_played();

    if (winner == Player::None && !board_full) {
      element_board = UiElements::build_board(state);
    } else {
      element_board = UiElements::declare_winner(state);
    }

    element_active_player = UiElements::active_player(state);

    screen_document = vbox({
        element_active_player,
        hbox({
            element_board | flex,
        }),
        element_instructions,
    });
  };

  draw_screen_document(state);

  auto screen = ScreenInteractive::TerminalOutput();
  auto renderer = Renderer([&] { return screen_document; });

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
      if (event == Event::n) {
        state.new_board();
      }
      break;
    }
    system("clear");

    state.run_board_check();

    const auto winner = state.get_winner();
    const auto board_full = state.board_is_fully_played();

    if (!(winner == Player::None && !board_full)) {
      draw_screen_document(state);
      state.new_board();
    } else {
      draw_screen_document(state);
    }


    // element_active_player = UiElements::active_player(state);

    return false;
  });

  screen.Loop(component);

  return EXIT_SUCCESS;
}
