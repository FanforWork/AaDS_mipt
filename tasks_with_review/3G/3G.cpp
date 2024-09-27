#include <iostream>
#include <vector>

void FindDifference(const std::vector<int64_t>& arr, int64_t& control,
                    int64_t& water_val, size_t& index) {
  if (arr[index] < control) {
    water_val += control - arr[index];
  } else {
    control = arr[index];
  }
}

void FindMaxval(const std::vector<int64_t>& arr, size_t& max_index) {
  for (size_t index = 1; index < arr.size(); ++index) {
    if (arr[index] > arr[max_index]) {
      max_index = index;
    }
  }
}

ino64_t CountWater(const std::vector<int64_t>& arr) {
  int64_t water_val = 0;
  size_t max_index = 0;
  FindMaxval(arr, max_index);
  int64_t control1 = arr.front();
  for (size_t index = 1; index < max_index; ++index) {
    FindDifference(arr, control1, water_val, index);
  }
  int64_t control2 = arr.back();
  for (size_t index = arr.size() - 2; index > max_index; --index) {
    FindDifference(arr, control2, water_val, index);
  }
  return water_val;
}

std::vector<int64_t> Input() {
  int64_t num;
  std::cin >> num;
  std::vector<int64_t> arr;
  int64_t value = 0;
  for (int64_t index = 0; index < num; ++index) {
    std::cin >> value;
    arr.push_back(value);
  }
  return arr;
}

void Output(std::vector<int64_t>& arr) { std::cout << CountWater(arr) << '\n'; }

int main() {
  std::vector<int64_t> arr;
  arr = Input();
  Output(arr);
  return 0;
}
