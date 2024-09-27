#include <iostream>
#include <vector>

class Heap {
 public:
  Heap() = default;

  explicit Heap(std::vector<int64_t>&& vector) : body_(std::move(vector)) {
    Heapify();
  }

  void Insert(int64_t num) {
    body_.push_back(num);
    decrease_.push_back(num);
    SiftUp(body_.size() - 1);
  }

  void GetMin() {
    decrease_.push_back(0);
    std::cout << GetTop() << '\n';
  }

  void ExtractMin() {
    decrease_.push_back(0);
    std::swap(body_.front(), body_.back());
    body_.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(u_int64_t index, int64_t delta) {
    decrease_.push_back(0);
    for (size_t ind = 0; ind < body_.size(); ++ind) {
      if (body_[ind] == decrease_[index - 1]) {
        body_[ind] -= delta;
        decrease_[index - 1] -= delta;
        SiftUp(ind);
      }
    }
  }

 private:
  void Heapify() {
    size_t ind = body_.size();
    while (ind > 0) {
      SiftDown(ind - 1);
      --ind;
    }
  }

  void SwapElements(size_t index1, size_t index2) {
    std::swap(body_[index1], body_[index2]);
  }

  void SiftUp(size_t index) {
    while (index != 0) {
      if (!compare_(body_[index], body_[Parent(index)])) {
        SwapElements(index, Parent(index));
        index = Parent(index);
      } else {
        break;
      }
    }
  }

  void SiftDown(size_t index) {
    while (index != body_.size() - 1) {
      size_t left_child_index = index * 2 + 1;
      size_t right_child_index = left_child_index + 1;
      if (left_child_index >= body_.size()) {
        return;
      }
      size_t min_child_index =
          (right_child_index < body_.size() &&
           compare_(body_[left_child_index], body_[right_child_index]))
              ? right_child_index
              : left_child_index;
      if (compare_(body_[index], body_[min_child_index])) {
        SwapElements(index, min_child_index);
        index = min_child_index;
      } else {
        return;
      }
    }
  }

  static size_t Parent(size_t index) { return (index - 1) / 2; }

  const int64_t& GetTop() const { return body_.front(); }

  std::vector<int64_t> body_;
  std::vector<int64_t> decrease_;
  std::greater<int64_t> compare_;
};

void Output(int64_t qnum) {
  std::string command;
  int64_t val;
  u_int64_t val0;
  int64_t index = 0;
  Heap heap;
  while (index < qnum) {
    std::cin >> command;
    if (command == "decreaseKey") {
      std::cin >> val0 >> val;
      heap.DecreaseKey(val0, val);
    }
    if (command == "insert") {
      std::cin >> val;
      heap.Insert(val);
    }
    if (command == "getMin") {
      heap.GetMin();
    }
    if (command == "extractMin") {
      heap.ExtractMin();
    }
    ++index;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t qnum;
  std::cin >> qnum;
  Output(qnum);
  return 0;
}
