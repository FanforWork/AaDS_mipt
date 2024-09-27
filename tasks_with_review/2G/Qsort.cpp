#include <algorithm>
#include <iostream>
#include <vector>

// Function to find the median of a small vector
auto FindSmallMedian(std::vector<int64_t> small_vec) {
  int64_t count = 0;
  for (size_t index = 0; index < small_vec.size() - 1; ++index) {
    ++count;
    for (auto iter = small_vec.begin(); iter < small_vec.end() - count;
         ++iter) {
      if (*iter > *(iter + 1)) {
        std::swap(*iter, *(iter + 1));
      }
    }
  }
  return small_vec[small_vec.size() / 2];
}

// Function to find the median of medians
template <typename Iterator>
Iterator SelectPivot(std::vector<int64_t>& vec, Iterator left, Iterator right) {
  std::vector<int64_t> sub_vec(vec.begin() + std::distance(vec.begin(), left),
                               vec.begin() + std::distance(vec.begin(), right));
  if (sub_vec.size() <= 5) {
    size_t dist = 0;
    auto smallest_element = FindSmallMedian(sub_vec);
    for (size_t index = 0; index < sub_vec.size(); ++index) {
      if (sub_vec[index] == smallest_element) {
        dist = index;
      }
    }
    return vec.begin() + std::distance(vec.begin(), left) + dist;
  }
  std::vector<int64_t> medians;
  for (size_t index = 0; index < sub_vec.size(); index += 5) {
    std::vector<int64_t> small_vec(
        sub_vec.begin() + index,
        sub_vec.begin() + std::min(index + 5, sub_vec.size()));
    medians.push_back(FindSmallMedian(small_vec));
  }
  size_t dist = 0;
  auto median_of_medianes = FindSmallMedian(medians);
  for (size_t index = 0; index < sub_vec.size(); ++index) {
    if (sub_vec[index] == median_of_medianes) {
      dist = index;
    }
  }
  return vec.begin() + std::distance(vec.begin(), left) + dist;
}

template <typename Iterator, typename Comparator>
std::pair<std::vector<int64_t>::iterator, std::vector<int64_t>::iterator>
Partition(std::vector<int64_t>& vec, Iterator left, Iterator right,
          Comparator compare) {
  Iterator pivot = SelectPivot(vec, left, right);
  std::vector<int64_t> less_pivot;
  std::vector<int64_t> equal_pivot;
  std::vector<int64_t> greater_pivot;
  for (Iterator iter = left; iter <= right; ++iter) {
    if (compare(*iter, *pivot)) {
      less_pivot.push_back(*iter);
    }
    if (!(compare(*iter, *pivot) || compare(*pivot, *iter))) {
      equal_pivot.push_back(*iter);
    }
    if (compare(*pivot, *iter)) {
      greater_pivot.push_back(*iter);
    }
  }
  for (size_t index = 0; index < less_pivot.size(); ++index) {
    vec[index + std::distance(vec.begin(), left)] = less_pivot[index];
  }
  for (size_t index = 0; index < equal_pivot.size(); ++index) {
    vec[std::distance(vec.begin(), left) + less_pivot.size() + index] =
        equal_pivot[index];
  }
  for (size_t index = 0; index < greater_pivot.size(); ++index) {
    vec[index + std::distance(vec.begin(), left) + less_pivot.size() +
        equal_pivot.size()] = greater_pivot[index];
  }
  Iterator iter_less = left + less_pivot.size();
  Iterator iter_eq = left + less_pivot.size() + equal_pivot.size() - 1;
  auto pair_iter = std::make_pair(iter_less, iter_eq);
  return pair_iter;
}

template <typename Iterator, typename Comparator>
void QuickSort(std::vector<int64_t>& vec, Iterator left, Iterator right,
               Comparator compare) {
  if (left >= right) {
    return;
  }
  auto index = Partition(vec, left, right, compare);
  QuickSort(vec, left, index.first - 1, compare);
  QuickSort(vec, index.second + 1, right, compare);
}

std::vector<int64_t> InputVector() {
  std::vector<int64_t> vec;
  int64_t num = 0;
  std::cin >> num;
  int64_t value = 0;
  for (int64_t i = 0; i < num; ++i) {
    std::cin >> value;
    vec.push_back(value);
  }
  return vec;
}

void Output(std::vector<int64_t>& vec) {
  for (int64_t ind : vec) {
    std::cout << ind << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::vector<int64_t> vec;
  vec = InputVector();
  auto comparator = [](const int64_t& val_1, const int64_t& val_2) {
    return val_1 < val_2;
  };
  QuickSort(vec, vec.begin(), vec.end() - 1, comparator);
  Output(vec);
  return 0;
}
