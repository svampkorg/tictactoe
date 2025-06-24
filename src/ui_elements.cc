#include "ui_elements.h"
#include "toestate.h"

const ftxui::Element UiElements::board_element(const Toestate &state) {

  using namespace ftxui;

  vector<Elements> lines;
  Elements line;
  auto board = state.get_board();

  for (int i = 0; i < board.size(); ++i) {

    string left = " ";
    string right = " ";

    auto board_place = [&](const Player place) {

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

      if (i == state.get_cursor_position()) {

        switch (state.get_active_player()) {

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
      window(text("Board"), gridbox(lines) | center) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 32);

  return document;
}

const ftxui::Element UiElements::winner_element(const Toestate &state) {
  using namespace ftxui;

  Element winner_text;

  switch (state.get_game_winner()) {

  case Player::Circle:
    winner_text = text("Circle winns!") | color(Color::Green);
    break;

  case Player::Cross:
    winner_text = text("Cross winns!") | color(Color::Red);
    break;

  case Player::None:
    winner_text = text("It's a draw!") | color(Color::White);
    break;
  }

  auto results = [&] {

    auto content = vbox({
        hbox({winner_text}) | color(Color::White),
    });
    return window(text(L" Game result! "), content);

  };

  Element document =
      results() | color(Color::NavajoWhite1);
      // window(text("Board"), winner()) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 32);

  return document;
}

const ftxui::Element UiElements::player_element(const Toestate &state) {

  using namespace ftxui;

  Element player_text;

  switch (state.get_active_player()) {

  case Player::Circle:
    player_text = text("It's Circle's turn") | color(Color::Green);
    break;

  case Player::Cross:
    player_text = text("It's Cross's turn") | color(Color::Red);
    break;

  default:
    break;
  }

  auto player_text_content = [&] {

    auto content = vbox({
        hbox({player_text}) | color(Color::White),
    });

    return content;
    // return window(text(L" Game result! "), content);
  };

  Element document =
      window(text("Player turn"), player_text_content()) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 32);

  return document;
}

const ftxui::Element UiElements::instructions_element(const Toestate &state) {

  using namespace ftxui;

  auto instructions_content = [&] {

    auto content = vbox({
        hbox({text("Move around using hjkl")}) | color(Color::White),
        hbox({text("Press space to make a move")}) | color(Color::White),
        hbox({text("Press n to start a new game")}) | color(Color::White),
        hbox({text("Press q to quit")}) | color(Color::White),
    });

    return content;

  };

  Element document =
      window(text("Instructions"), instructions_content()) | color(Color::NavajoWhite1);

  document = document | size(WIDTH, ftxui::EQUAL, 32);

  return document;
}
