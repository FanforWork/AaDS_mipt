#include <iostream>
#include <vector>

namespace MaxBorder {
const int32_t kRight = 1e9;
}

bool CheckOccupyCount(const std::vector<int32_t>& arr, int32_t count_festrals,
                      int32_t dist) {
  int32_t occupy_count = 1;
  int32_t last_occupied = arr[0];
  for (int32_t ind : arr) {
    if (last_occupied + dist <= ind) {
      ++occupy_count;
      last_occupied = ind;
    }
  }
  return occupy_count >= count_festrals;
}

std::vector<int32_t> Input(int32_t count_festrals) {
  std::vector<int32_t> arr;
  int32_t value = 0;
  int32_t num = 0;
  std::cin >> num >> count_festrals;
  for (int32_t ind = 0; ind < num; ++ind) {
    std::cin >> value;
    arr.push_back(value);
  }
  return arr;
}

template <typename Predicate>
int32_t BinSearch(const std::vector<int32_t>& arr, int32_t count_festrals,
                  Predicate predicate) {
  int32_t left = 0;
  int32_t right = MaxBorder::kRight;
  while (left < right) {
    int32_t dist = (left + right) / 2;
    if (predicate(arr, count_festrals, dist)) {
      left = dist + 1;
    } else {
      right = dist;
    }
  }
  return left - 1;
}

int main() {
  int32_t value = 0;
  int32_t count_festrals = 0;
  std::vector<int32_t> arr;
  arr = Input(count_festrals);
  value = BinSearch(arr, count_festrals, CheckOccupyCount);
  std::cout << value;
  return 0;
}