#include <iostream>
#include <vector>

struct Coords {
  int64_t x_coord;
  int64_t y_coord;
  int64_t z_coord;
};

class FenwickTree {
 public:
  FenwickTree() = default;

  FenwickTree(int64_t num)
      : base_(num, std::vector<std::vector<int64_t>>(
                       num, std::vector<int64_t>(num, 0))),
        num_(num) {}

  int64_t GetSum(Coords first_pos, Coords second_pos) const {
    return GetPrefSum(second_pos.x_coord, second_pos.y_coord,
                      second_pos.z_coord) -
           GetPrefSum(second_pos.x_coord, second_pos.y_coord,
                      first_pos.z_coord - 1) -
           GetPrefSum(second_pos.x_coord, first_pos.y_coord - 1,
                      second_pos.z_coord) -
           GetPrefSum(first_pos.x_coord - 1, second_pos.y_coord,
                      second_pos.z_coord) +
           GetPrefSum(second_pos.x_coord, first_pos.y_coord - 1,
                      first_pos.z_coord - 1) +
           GetPrefSum(first_pos.x_coord - 1, first_pos.y_coord - 1,
                      second_pos.z_coord) +
           GetPrefSum(first_pos.x_coord - 1, second_pos.y_coord,
                      first_pos.z_coord - 1) -
           GetPrefSum(first_pos.x_coord - 1, first_pos.y_coord - 1,
                      first_pos.z_coord - 1);
  }

  void Update(size_t x_coord, size_t y_coord, size_t z_coord, int64_t val) {
    UpdateVal(x_coord, y_coord, z_coord, val);
  }

 private:
  static int64_t FindFunc(size_t value) { return value & (value + 1); }

  static int64_t SetFunc(size_t value) { return value | (value + 1); }

  int64_t GetPrefSum(size_t x_coord, size_t y_coord, size_t z_coord) const {
    int64_t result = 0;
    for (int64_t i = x_coord; i >= 0; i = FindFunc(i) - 1) {
      for (int64_t j = y_coord; j >= 0; j = FindFunc(j) - 1) {
        for (int64_t k = z_coord; k >= 0; k = FindFunc(k) - 1) {
          result += base_[i][j][k];
        }
      }
    }
    return result;
  }

  void UpdateVal(size_t x_coord, size_t y_coord, size_t z_coord,
                 int64_t delta) {
    for (int64_t i = x_coord; i < num_; i = SetFunc(i)) {
      for (int64_t j = y_coord; j < num_; j = SetFunc(j)) {
        for (int64_t k = z_coord; k < num_; k = SetFunc(k)) {
          base_[i][j][k] += delta;
        }
      }
    }
  }

  std::vector<std::vector<std::vector<int64_t>>> base_;
  int64_t num_;
};

void CountValue(int64_t num) {
  std::string command;
  int64_t val = 0;
  int64_t x_coord = 0;
  int64_t y_coord = 0;
  int64_t z_coord = 0;
  FenwickTree tree(num);
  while (true) {
    std::cin >> command;
    if (command == "1") {
      std::cin >> x_coord >> y_coord >> z_coord >> val;
      tree.Update(x_coord, y_coord, z_coord, val);
    }
    if (command == "2") {
      Coords first_pos;
      Coords second_pos;
      std::cin >> first_pos.x_coord >> first_pos.y_coord >> first_pos.z_coord >>
          second_pos.x_coord >> second_pos.y_coord >> second_pos.z_coord;
      std::cout << tree.GetSum(first_pos, second_pos) << '\n';
    }
    if (command == "3") {
      return;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t num = 0;
  std::cin >> num;
  CountValue(num);
  return 0;
}
