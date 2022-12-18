#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int total_score_following_strategy_guide(std::string const &file_path);
int determine_player_single_round_score(char opponent, char player);

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
    char player{};

    ss >> opponent;
    ss >> player;

    total_score += determine_player_single_round_score(opponent, player);
    std::cout << opponent << "+" << player << "="
              << determine_player_single_round_score(opponent, player)
              << std::endl;
  }

  return total_score;
}

/*
 * Opponent's symbols: Rock = A, Paper = B, Scissors = C
 * Player's symbols:   Rock = X, Paper = Y, Scissors = Z
 */
int determine_player_single_round_score(char opponent, char player) {
  int round_score{0};
  int symbol_choice_score{0};

  // Is this a win, draw, or lose scenario (its lose by default)?
  if ((opponent == 'A' && player == 'Y') ||
      (opponent == 'B' && player == 'Z') ||
      (opponent == 'C' && player == 'X')) {
    round_score = 6;
  } else if ((opponent == 'A' && player == 'X') ||
             (opponent == 'B' && player == 'Y') ||
             (opponent == 'C' && player == 'Z')) {
    round_score = 3;
  }

  if (player == 'X') {
    symbol_choice_score = 1;
  } else if (player == 'Y') {
    symbol_choice_score = 2;
  } else {  // We can assume its Z, no need for error handling.
    symbol_choice_score = 3;
  }

  return round_score + symbol_choice_score;
}