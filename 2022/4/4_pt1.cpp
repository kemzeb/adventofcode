#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int sum_num_assignment_pairs_with_fully_contained_range(
    std::string const &input_file_path);
std::vector<std::vector<int>> parse_for_assignment_pair(std::string const &str);

int main(int argc, char *argv[]) {
  std::string file_path{};

  if (argc < 2) {
    return 1;
  }
  file_path = argv[1];
  std::cout << sum_num_assignment_pairs_with_fully_contained_range(file_path)
            << std::endl;

  return 0;
}

int sum_num_assignment_pairs_with_fully_contained_range(
    std::string const &input_file_path) {
  std::ifstream input_file{input_file_path};
  std::string line;
  int assignment_pairs_sum{0};

  while (getline(input_file, line)) {
    auto assignment_pair = parse_for_assignment_pair(line);

    auto f_partner_starting_id = assignment_pair[0][0];
    auto s_partner_starting_id = assignment_pair[1][0];
    auto f_partner_ending_id = assignment_pair[0][1];
    auto s_partner_ending_id = assignment_pair[1][1];

    if (f_partner_starting_id == s_partner_starting_id) {
      // If these values were to equal, one will ALWAYS be fully contained
      // within the other.
      assignment_pairs_sum++;
      continue;
    } else if (s_partner_starting_id < f_partner_starting_id &&
               f_partner_ending_id > s_partner_ending_id) {
      // First partner's range cannot be fully contained in second partner's
      // range.
      continue;
    } else if (f_partner_starting_id < s_partner_starting_id &&
               s_partner_ending_id > f_partner_ending_id) {
      // Second partner's range cannot be fully contained in first partner's
      // range.
      continue;
    }
    // If we reached here, we encountered a partner that has a range that can
    // be fully contained within the other partner.
    assignment_pairs_sum++;
  }

  return assignment_pairs_sum;
}

std::vector<std::vector<int>> parse_for_assignment_pair(
    std::string const &str) {
  std::vector<std::vector<int>> assignment_pair{};
  auto delimeter_idx = str.find(',');
  auto f_partner_str = str.substr(0, delimeter_idx);
  auto s_partner_str = str.substr(delimeter_idx + 1);

  auto f_partner_delimeter_idx = f_partner_str.find('-');
  auto starting_section =
      stoi(f_partner_str.substr(0, f_partner_delimeter_idx));
  auto ending_section = stoi(f_partner_str.substr(f_partner_delimeter_idx + 1));
  assignment_pair.push_back({starting_section, ending_section});

  auto s_partner_delimeter_idx = s_partner_str.find('-');
  starting_section = stoi(s_partner_str.substr(0, s_partner_delimeter_idx));
  ending_section = stoi(s_partner_str.substr(s_partner_delimeter_idx + 1));
  assignment_pair.push_back({starting_section, ending_section});

  return assignment_pair;
}