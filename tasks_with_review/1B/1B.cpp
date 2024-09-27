#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace DecNum {
const int32_t kDecnum = 10;
}

void LogarifmPref(std::vector<double>& logarifms, std::vector<double>& arr) {
  logarifms.push_back(std::log(arr[0]));
  for (size_t ind = 1; ind < arr.size(); ++ind) {
    logarifms.push_back(logarifms[ind - 1] + std::log(arr[ind]));
  }
}

void Output(std::vector<double>& logarifms, std::vector<double>& arr,
            int32_t& left, int32_t& right) {
  std::cout << '\n';
  std::cout << std::fixed << std::setprecision(DecNum::kDecnum)
            << std::pow(std::exp(1.0), (logarifms[right] - logarifms[left] +
                                        std::log(arr[left])) /
                                           (right - left + 1));
  std::cout << '\n';
}

void Input(std::vector<double>& arr) {
  int32_t num = 0;
  std::cin >> num;
  double value = 0;
  for (int32_t count = 0; count < num; ++count) {
    std::cin >> value;
    arr.push_back(value);
  }
}

void QueryProccessing(std::vector<double>& logarifms,
                      std::vector<double>& arr) {
  int32_t query = 0;
  int32_t left = 0;
  int32_t right = 0;
  std::cin >> query;
  LogarifmPref(logarifms, arr);
  for (int32_t i = 0; i < query; ++i) {
    std::cin >> left >> right;
    Output(logarifms, arr, left, right);
  }
}

int main() {
  std::vector<double> arr;
  std::vector<double> logarifms;
  Input(arr);
  QueryProccessing(logarifms, arr);
  return 0;
}