#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

const int MAX_NUM = 30000;

std::unordered_map<int, int> brack_map;
std::array<char, MAX_NUM> init() { return std::array<char, MAX_NUM>{{0}}; }

int find_next(std::string &inputs, int index) {
  auto search = brack_map.find(index);
  if (search != brack_map.end()) return search->second;
  int begin = index, num = 1;
  while (++index < inputs.length()) {
    if (inputs[index] == '[') {
      num++;
    } else if (inputs[index] == ']') {
      num--;
      if (num == 0) {
        brack_map.insert({begin, index - 1});
        brack_map.insert({index, begin - 1});
        return index - 1;
      }
    }
  }
  throw "Inputs is invalid\n";
}

int main(int argc, char *argv[]) {
  std::array<char, MAX_NUM> nums = init();
  std::string inputs;
  int index = 0;
  std::ifstream file("inputs.txt");
  if (file.is_open()) {
    std::getline(file, inputs);
  }
  for (int i = 0; i < inputs.length(); i++) {
    char num = inputs[i];
    switch (num) {
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
          goto Exception;
        }
        break;
      case '<':
        if (index > 0) {
          index--;
        } else {
          goto Exception;
        }
        break;
      case '.':
        std::cout << nums[index];
        break;
      case '[':
        find_next(inputs, i);
        if (nums[index] == 0) {
          i = find_next(inputs, i);
        }
        break;
      case ']':
        if (nums[index] != 0) {
          i = find_next(inputs, i);
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
Exception:
  throw "Inputs is invalid\n";
}