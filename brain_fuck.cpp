#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

const int MAX_NUM = 30000;
const int INVALID_INDEX = -2;

std::unordered_map<int, int> brack_map;
std::array<char, MAX_NUM> init() { return std::array<char, MAX_NUM>{{0}}; }

int find_match(const std::string &inputs, int index, char c) {
  auto search = brack_map.find(index);
  if (search != brack_map.end())
    return search->second;
  if (c == ']') {
    std::cerr << "Input Error, there is no match with char \'" << c
              << "\' in position:" << index + 1 << std::endl;
    return INVALID_INDEX;
  }
  int begin = index, num = 1;
  while (++index < inputs.length()) {
    if (inputs[index] == '[') {
      num++;
    } else if (inputs[index] == ']') {
      num--;
    }
    if (num == 0) {
      brack_map.insert({begin, index - 1});
      brack_map.insert({index, begin - 1});
      return index - 1;
    } else if (num < 0) {
      break;
    }
  }
  std::cerr << "Input Error, there is no match with char \'" << c
            << "\' in position:" << index + 1 << std::endl;
  return INVALID_INDEX;
}

int processBf(const std::string &inputs) {
  std::array<char, MAX_NUM> nums = init();
  int index = 0;
  for (int i = 0; i < inputs.length(); i++) {
    char c = inputs[i];
    switch (c) {
      case '+':
        nums[index]++;
        break;
      case '-':
        nums[index]--;
        break;
      case '>':
        if (index < MAX_NUM - 1) {
          index++;
        } else {
          std::cerr
              << "Compute error, beyond the upper bound of array in position:"
              << i + 1 << std::endl;
          return -2;
        }
        break;
      case '<':
        if (index > 0) {
          index--;
        } else {
          std::cerr
              << "Compute error, below the lower bound of array in position:"
              << i + 1 << std::endl;
          return -2;
        }
        break;
      case '.':
        std::cout << nums[index];
        break;
      case '[':
        find_match(inputs, i, c);
        if (nums[index] == 0) {
          i = find_match(inputs, i, c);
          if (i == INVALID_INDEX) {
            return -1;
          }
        }
        break;
      case ']':
        if (nums[index] != 0) {
          i = find_match(inputs, i, c);
          if (i == INVALID_INDEX) {
            return -1;
          }
        }
        break;
      case ',':
        std::cin >> nums[index];
        break;
      default:
        break;
    }
  }
  return 0;
}

std::string charProcess(const char c) {
  std::string rest;
  int quotient = c / 10;
  int remainder = c % 10;
  while (quotient) {
    rest += "+";
    quotient--;
  }
  rest += "[>++++++++++<-]>";
  while (remainder) {
    rest += "+";
    remainder--;
  }
  rest += ".>";
  return rest;
}

std::string processStr(std::string inputs) {
  std::string rest;
  for (const auto &c : inputs) {
    rest += (charProcess(c) + "\n");
  }
  return rest;
}

int main(int argc, char *argv[]) {
  std::string inputs =
      ">++++++++\
          [<+++++++++> - ]<.> ++++[<+++++++> - ]<+.+++++++..+++.> >\
      ++++++[<+++++++> - ]<++.------------.> ++++++[<+++++++++> -\
  ]<+.<.+++.------.--------.>> > ++++[<++++++++> - ] < +.";
  processBf(inputs);

  inputs = "Test encode with bf\n";
  int rest = processBf(processStr(inputs));
  return rest;
}