#include <iostream>
#include <stack>
#include <string>

void LeftBracketCase(std::stack<int32_t>& left_brackets, int32_t& index,
                     int32_t& bracket_balance) {
  left_brackets.push(index);
  ++index;
  ++bracket_balance;
}

void RightBracketCase(std::stack<int32_t>& right_brackets, int32_t& index) {
  right_brackets.push(index);
  ++index;
}

void BothBracketsCase(std::stack<int32_t>& left_brackets,
                      std::stack<int32_t>& right_brackets, int32_t& index,
                      int32_t& bracket_balance, int32_t& count) {
  --bracket_balance;
  left_brackets.pop();
  if (!right_brackets.empty() && bracket_balance <= 0) {
    count = index - left_brackets.top() - right_brackets.top();
  } else {
    count = index - left_brackets.top();
  }
  ++index;
}

int32_t FindMax(std::string& sequence) {
  std::stack<int32_t> left_brackets;
  std::stack<int32_t> right_brackets;
  left_brackets.push(0);
  int32_t index = 1;
  int32_t count = 0;
  int32_t max_subseq = 0;
  int32_t bracket_balance = 0;
  for (size_t ind = 0; ind < sequence.size(); ++ind) {
    if (sequence[ind] == '(') {
      LeftBracketCase(left_brackets, index, bracket_balance);
    }
    if (sequence[ind] == ')' && left_brackets.size() == 1) {
      RightBracketCase(right_brackets, index);
    }
    if (sequence[ind] == ')' && left_brackets.size() != 1) {
      BothBracketsCase(left_brackets, right_brackets, index, bracket_balance,
                       count);
    }
    if (count > max_subseq) {
      max_subseq = count;
    }
  }
  return max_subseq;
}

int main() {
  std::string sequence;
  std::cin >> sequence;
  int32_t max_seq = FindMax(sequence);
  std::cout << max_seq << '\n';
  return 0;
}