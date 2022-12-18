#include <fstream>
#include <iostream>
#include <list>
#include <string>

int find_elf_with_max_calories(std::string const file_path);
std::list<int> get_total_calories_by_elf(std::string const file_path);

int main(int argc, char* argv[]) {
  std::string file_path{};

  if (argc < 2) {
    return 1;
  }
  file_path = argv[1];
  std::cout << find_elf_with_max_calories(file_path) << std::endl;

  return 0;
}

int find_elf_with_max_calories(std::string const file_path) {
  int max_calories{-1};
  std::list<int> total_calories_by_elf{get_total_calories_by_elf(file_path)};

  for (auto total_calories : total_calories_by_elf) {
    if (max_calories < total_calories) {
      max_calories = total_calories;
    }
  }

  return max_calories;
}

std::list<int> get_total_calories_by_elf(std::string const file_path) {
  std::ifstream calories_file{file_path};
  std::list<int> total_calories_by_elf{};
  int runningTotalCals{0};

  if (calories_file.is_open()) {
    std::string line{};

    while (getline(calories_file, line)) {
      // getline discards newlines. The more you know.
      if (line.empty()) {
        total_calories_by_elf.push_back(runningTotalCals);
        runningTotalCals = 0;
        continue;
      }
      int calorie{std::stoi(line)};
      runningTotalCals += calorie;
    }
    // If there is no space at the very end of the file, we don't capture the
    // last elf's calories. Make sure to account for this.
    if (runningTotalCals != 0) {
      total_calories_by_elf.push_back(runningTotalCals);
    }

    calories_file.close();
  }

  return total_calories_by_elf;
}