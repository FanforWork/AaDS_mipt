#include <iostream>
#include <vector>

namespace InitialData {
const size_t kHashMapSize = 10;
}

class HashMap {
 public:
  HashMap() : body_(InitialData::kHashMapSize) {}
  void GetElem(int32_t value) {
    int32_t key = HashFunc(value);
    int32_t count = 0;
    for (size_t ind = 0; ind < body_[key].size(); ++ind) {
      if (body_[key][ind] == value) {
        ++count;
      }
    }
    if (count > 0) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
  void Insert(int32_t value) {
    int32_t key = HashFunc(value);
    int32_t count = 0;
    for (size_t ind = 0; ind < body_[key].size(); ++ind) {
      if (body_[key][ind] == value) {
        ++count;
      }
    }
    if (count == 0) {
      body_[key].push_back(value);
    }
  }
  void Delete(int32_t value) {
    int32_t key = HashFunc(value);
    for (size_t ind = 0; ind < body_[key].size(); ++ind) {
      if (body_[key][ind] == value) {
        std::swap(body_[key][ind], body_[key].back());
        body_[key].pop_back();
        break;
      }
    }
  }

 private:
  std::vector<std::vector<int32_t> > body_;
  int32_t HashFunc(int32_t value) { return value % body_.size(); }
};

void QuerryProccessing(int32_t num) {
  int32_t val = 0;
  HashMap hash_map;
  std::string command;
  for (int32_t index = 0; index < num; ++index) {
    std::cin >> command;
    if (command == "+") {
      std::cin >> val;
      hash_map.Insert(val);
    }
    if (command == "?") {
      std::cin >> val;
      hash_map.GetElem(val);
    }
    if (command == "-") {
      std::cin >> val;
      hash_map.Delete(val);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t num = 0;
  std::cin >> num;
  QuerryProccessing(num);
  return 0;
}
