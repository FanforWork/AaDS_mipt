#include <iostream>
#include <vector>

std::vector<int32_t> Merge(std::vector<int32_t>& arr_left,
                           std::vector<int32_t>& arr_right) {
  size_t ind_left = 0;
  size_t ind_right = 0;
  std::vector<int32_t> vec;
  while (ind_left < arr_left.size() && ind_right < arr_right.size()) {
    if (arr_left[ind_left] < arr_right[ind_right]) {
      vec.push_back(arr_left[ind_left]);
      ++ind_left;
    } else {
      vec.push_back(arr_right[ind_right]);
      ++ind_right;
    }
  }
  while (ind_left < arr_left.size()) {
    vec.push_back(arr_left[ind_left]);
    ++ind_left;
  }
  while (ind_right < arr_right.size()) {
    vec.push_back(arr_right[ind_right]);
    ++ind_right;
  }
  return vec;
}

void Output(std::vector<int32_t>& vec) {
  for (size_t ind = 0; ind < vec.size(); ++ind) {
    std::cout << vec[ind] << ' ';
  }
}

std::vector<int32_t> VecEvenCase(std::vector<int32_t> vec, int32_t knum) {
  int32_t num;
  for (int32_t index = 0; index < knum / 2; ++index) {
    std::vector<int32_t> copy;
    std::cin >> num;
    std::vector<int32_t> arr_left(num);
    for (int32_t ind = 0; ind < num; ++ind) {
      std::cin >> arr_left[ind];
    }
    std::cin >> num;
    std::vector<int32_t> arr_right(num);
    for (int32_t ind = 0; ind < num; ++ind) {
      std::cin >> arr_right[ind];
    }
    copy = Merge(arr_left, arr_right);
    vec = Merge(vec, copy);
    arr_right.clear();
    copy.clear();
    arr_left.clear();
  }
  return vec;
}

std::vector<int32_t> VecOddCase(std::vector<int32_t> vec, int32_t knum) {
  int32_t num;
  for (int32_t index = 0; index < knum / 2; ++index) {
    std::vector<int32_t> copy;
    std::cin >> num;
    std::vector<int32_t> arr_left(num);
    for (int32_t ind = 0; ind < num; ++ind) {
      std::cin >> arr_left[ind];
    }
    std::cin >> num;
    std::vector<int32_t> arr_right(num);
    for (int32_t ind = 0; ind < num; ++ind) {
      std::cin >> arr_right[ind];
    }
    copy = Merge(arr_left, arr_right);
    vec = Merge(vec, copy);
    arr_right.clear();
    copy.clear();
    arr_left.clear();
  }
  std::cin >> num;
  std::vector<int32_t> arr_right(num);
  for (int32_t ind = 0; ind < num; ++ind) {
    std::cin >> arr_right[ind];
  }
  vec = Merge(vec, arr_right);
  arr_right.clear();
  return vec;
}

void Input(int32_t& knum) { std::cin >> knum; }

std::vector<int32_t> Merger(std::vector<int32_t> vec, int32_t& knum) {
  if (knum % 2 == 0) {
    return VecEvenCase(vec, knum);
  }
  if (knum % 2 != 0) {
    return VecOddCase(vec, knum);
  }
  return VecEvenCase(vec, knum);
}

int main() {
  std::vector<int32_t> vec;
  int32_t knum = 0;
  Input(knum);
  vec = Merger(vec, knum);
  Output(vec);
  return 0;
}
