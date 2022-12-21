#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

int sum_priorities_of_duplicate_items_in_group(std::string const &string);
char find_duplicate_rucksack_item(std::string const &items_string);
int get_item_priority_num(char item);

int main(int argc, char *argv[]) {
  std::string file_path{};

  if (argc < 2) {
    return 1;
  }
  file_path = argv[1];
  std::cout << sum_priorities_of_duplicate_items_in_group(file_path)
            << std::endl;

  return 0;
}

int sum_priorities_of_duplicate_items_in_group(std::string const &file_path) {
  std::ifstream rucksacks_file{file_path};
  std::string line;
  int const SIZE = 256;
  int item_count[SIZE];  // Chars passed as indices. Values represent their
                         // count.
  int priorities_sum{0};
  int curr_rucksack_count{0};

  while (getline(rucksacks_file, line)) {
    std::unordered_set<char> item_set{};
    curr_rucksack_count++;

    // Get unique items from line using a set.
    for (size_t i = 0; i < line.size(); i++) {
      item_set.insert(line[i]);
    }

    // Store unique item count into an array.
    for (auto unique_item : item_set) {
      item_count[unique_item]++;
    }

    if (curr_rucksack_count != 3) {
      continue;
    }

    // We have a group. Find an element in item_count that == 3, representing a
    // item that is within all 3 rucksacks.
    for (char ch = 0; ch < SIZE; ch++) {
      auto count = item_count[ch];

      if (count == 3) {
        char duplicate_item{ch};
        int priority_num{get_item_priority_num(duplicate_item)};

        priorities_sum += priority_num;
        break;  // Should only be 1 duplicate item.
      }
    }

    // Reset item_count so that we can use it for the next group.
    for (int i = 0; i < SIZE; i++) {
      item_count[i] = 0;
    }

    // Reset rucksack count for the next group.
    curr_rucksack_count = 0;
  }

  return priorities_sum;
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