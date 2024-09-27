#include <algorithm>
#include <iostream>
#include <vector>

// сюда закинули константы как в требованиях к коду
namespace ArrElem {
const int32_t kVal1 = 123;
const int32_t kVal2 = 45;
const int32_t kDiv = 10004321;
};  // namespace ArrElem

// тут подбираем пивот
int32_t ChoosePivot(std::vector<int32_t>& arr, int32_t left, int32_t right) {
  return arr[(left + right) / 2];
}

// здесь мы слева от пивота ставим тех кто меньше справа наоборот больше
int32_t Partition(std::vector<int32_t>& arr, int32_t left, int32_t right) {
  int32_t pivot = ChoosePivot(arr, left, right);
  int32_t ind = left;
  int32_t jnd = right;
  while (true) {
    while (arr[ind] < pivot) {
      ++ind;
    }
    while (arr[jnd] > pivot) {
      --jnd;
    }
    if (ind >= jnd) {
      return jnd;
    }
    std::swap(arr[ind], arr[jnd]);
    if (arr[ind] != pivot) {
      ++ind;
    } else {
      --jnd;
    }
  }
}

// ну рекурсия делает больно ml поэтому пришлось её заменить
int32_t KthStat(std::vector<int32_t>& arr, int32_t left, int32_t right,
                int32_t ket) {
  while (true) {
    int32_t index = Partition(arr, left, right);
    if (index == ket) {
      return arr[index];
    }
    if (index < ket) {
      left = index + 1;
    } else {
      right = index - 1;
    }
  }
}

void Input(std::vector<int32_t>& vec, int32_t& k_num, int32_t& num) {
  int32_t val1 = 0;
  int32_t val2 = 0;
  std::cin >> num;
  std::cin >> k_num >> val1 >> val2;
  vec.push_back(val1);
  vec.push_back(val2);
  for (int32_t index = 2; index < num; ++index) {
    vec.push_back(
        (vec[index - 1] * ArrElem::kVal1 + vec[index - 2] * ArrElem::kVal2) %
        ArrElem::kDiv);
  }
}

void Output(std::vector<int32_t>& vec, int32_t& k_num, int32_t& num) {
  std::cout << KthStat(vec, 0, num - 1, k_num - 1) << '\n';
}

int main() {
  std::vector<int32_t> vec;
  int32_t k_num = 0;
  int32_t num = 0;
  Input(vec, k_num, num);
  Output(vec, k_num, num);
}
