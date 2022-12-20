#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

// NOTE: These functions assume the input file only contains lowercase or
// uppercase English characters.

int sum_priorities_of_duplicate_rucksack_items(std::string const &file_path);
char find_duplicate_rucksack_item(std::string const &items_string);
int get_item_priority_num(char item);

int main(int argc, char *argv[]) {
  std::string file_path{};

  if (argc < 2) {
    return 1;
  }
  file_path = argv[1];
  std::cout << sum_priorities_of_duplicate_rucksack_items(file_path)
            << std::endl;

  return 0;
}

int sum_priorities_of_duplicate_rucksack_items(std::string const &file_path) {
  std::ifstream rucksacks_file{file_path};
  std::string line;
  int priorities_sum{0};

  while (getline(rucksacks_file, line)) {
    char duplicate_item{find_duplicate_rucksack_item(line)};
    int priority_num{get_item_priority_num(duplicate_item)};

    priorities_sum += priority_num;
  }

  return priorities_sum;
}

char find_duplicate_rucksack_item(std::string const &items_string) {
  auto rightIdx = items_string.size() - 1;

  // Find the index of the middle rucksack item.
  size_t midIdx{rightIdx / 2};

  // Store elements on left side of midIdx into a set.
  std::unordered_set<char> item_set{};

  for (size_t i = 0; i <= midIdx; i++) {
    item_set.insert(items_string[i]);
  }

  // Check if right side has an element within the set.
  for (auto i = midIdx + 1; i < items_string.size(); i++) {
    auto item = items_string[i];

    if (item_set.count(item) == 1) {
      return item;
    }
  }

  return ' ';
}

// Priority uppercase = priority lowercase + 26
// Priority lowercase = item - a + 1
int get_item_priority_num(char item) {
  int priority_num{0};

  if (item >= 'a' && item <= 'z') {
    priority_num = item - 'a' + 1;
  } else if (item >= 'A' && item <= 'Z') {
    priority_num = tolower(item) - 'a' + 1 + 26;
  }

  return priority_num;
}