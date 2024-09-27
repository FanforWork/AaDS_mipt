#include <iostream>
#include <limits>
#include <vector>

namespace CountStuff {
const int64_t kBytesize = 8;
const int64_t kBitesize = 256;
}  // namespace CountStuff

// получаем n-тый байт числа
int64_t GetByte(int64_t number, size_t byte) {
  return number >> (CountStuff::kBytesize * byte) & (CountStuff::kBitesize - 1);
}

// сортировка подсчетом массива чисел по n-тому байту
void CountingSort(std::vector<int64_t>& arr, size_t size, size_t byte) {
  std::vector<int64_t> counters(CountStuff::kBitesize, 0);
  std::vector<int64_t> output(size);
  // считаем количество чисел с разными значениями байта (от 0 до 255)
  for (size_t index = 0; index < size; ++index) {
    ++counters[GetByte(arr[index], byte)];
  }
  // расчитываем первые индексы для вставки чисел
  for (size_t index = 1; index < CountStuff::kBitesize; ++index) {
    counters[index] += counters[index - 1];
  }
  // создаем отсортированный массив результатов
  int64_t ind = size - 1;
  while (ind != -1) {
    output[--counters[GetByte(arr[ind], byte)]] = arr[ind];
    --ind;
  }
  // переписываем отсортированный массив в исходный
  for (size_t index = 0; index < size; ++index) {
    arr[index] = output[index];
  }
}

size_t BytesCounter() { return sizeof(int64_t); }

// сортировка LSD
void LSD(std::vector<int64_t>& arr) {
  size_t total_bytes = BytesCounter();
  for (size_t byte = 0; byte < total_bytes; ++byte) {
    CountingSort(arr, arr.size(), byte);
  }
}

std::vector<int64_t> VectorBuild() {
  size_t num;
  std::cin >> num;
  std::vector<int64_t> vec;
  int64_t value = 0;
  for (size_t index = 0; index < num; ++index) {
    std::cin >> value;
    vec.push_back(value);
  }
  return vec;
}

void Output(const std::vector<int64_t>& vec) {
  for (auto value : vec) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int64_t> vec;
  vec = VectorBuild();
  LSD(vec);
  Output(vec);
  return 0;
}

