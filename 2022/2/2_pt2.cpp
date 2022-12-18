#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int total_score_following_strategy_guide(std::string const &file_path);
int determine_player_single_round_score(char opponent,
                                        char desired_round_result);
int main(int argc, char *argv[]) {
  std::string file_path{};

  if (argc < 2) {
    return 1;
  }
  file_path = argv[1];
  std::cout << total_score_following_strategy_guide(file_path) << std::endl;

  return 0;
}

int total_score_following_strategy_guide(std::string const &file_path) {
  std::ifstream strategy_guide_file{file_path};
  std::string line;
  int total_score{0};

  while (std::getline(strategy_guide_file, line)) {
    std::stringstream ss{line};
    char opponent{};
    char round_result{};

    ss >> opponent;
    ss >> round_result;

    total_score += determine_player_single_round_score(opponent, round_result);
  }

  return total_score;
}

/*
 * Opponent's symbols: Rock = A, Paper = B, Scissors = C
 * Round result symbols:   Lose = X, Draw = Y, Win = Z
 */
int determine_player_single_round_score(char opponent,
                                        char desired_round_result) {
  int round_score{0};
  char player{};

  // Note: For consistency player's symbol will follow opponent's symbol layout.
  // Note: Readability sucks here and I could find a way to wiggle in an enum
  // type here or there. But hey, these are just coding puzzles!
  switch (desired_round_result) {
    case 'X':  // Lose case
      switch (opponent) {
        case 'A':
          player = 'C';
          break;
        case 'B':
          player = 'A';
          break;
        case 'C':
          player = 'B';
          break;
      }
      break;
    case 'Y':  // Draw case
      round_score = 3;
      switch (opponent) {
        case 'A':
          player = 'A';
          break;
        case 'B':
          player = 'B';
          break;
        case 'C':
          player = 'C';
          break;
      }
      break;
    case 'Z':  // Win case.
      round_score = 6;
      switch (opponent) {
        case 'A':
          player = 'B';
          break;
        case 'B':
          player = 'C';
          break;
        case 'C':
          player = 'A';
          break;
      }
      break;
  }

  int symbol_choice_score{0};

  if (player == 'A') {
    symbol_choice_score = 1;
  } else if (player == 'B') {
    symbol_choice_score = 2;
  } else {  // We can assume its C, no need for error handling.
    symbol_choice_score = 3;
  }

  return round_score + symbol_choice_score;
}