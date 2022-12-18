#include <fstream>
#include <iostream>
#include <queue>

int sum_calories_of_top_three_elves(std::string const file_path);
std::priority_queue<int> get_total_calories_by_elf(std::string const file_path);

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    return 1;
  }
  std::string file_path{argv[1]};
  std::cout << sum_calories_of_top_three_elves(file_path) << std::endl;

  return 0;
}

int sum_calories_of_top_three_elves(std::string const file_path) {
  std::priority_queue<int> total_calories_by_elf{
      get_total_calories_by_elf(file_path)};
  int sum{0};

  if (total_calories_by_elf.size() >= 3) {
    for (int i = 0; i < 3; i++) {
      sum += total_calories_by_elf.top();
      total_calories_by_elf.pop();
    }
  }

  return sum;
}

std::priority_queue<int> get_total_calories_by_elf(
    std::string const file_path) {
  std::ifstream calories_file{file_path};
  std::priority_queue<int> total_calories_by_elf{};
  int runningTotalCals{0};

  if (calories_file.is_open()) {
    std::string line{};

    while (getline(calories_file, line)) {
      // getline discards newlines. The more you know.
      if (line.empty()) {
        total_calories_by_elf.push(runningTotalCals);
        runningTotalCals = 0;
        continue;
      }
      int calorie{std::stoi(line)};
      runningTotalCals += calorie;
    }
    // If there is no space at the very end of the file, we don't capture the
    // last elf's calories. Make sure to account for this.
    if (runningTotalCals != 0) {
      total_calories_by_elf.push(runningTotalCals);
    }

    calories_file.close();
  }

  return total_calories_by_elf;
}
