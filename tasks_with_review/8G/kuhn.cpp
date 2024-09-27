#include <iostream>
#include <vector>

class Graph {
 public:
  Graph(int64_t vertex_num, int64_t edges_num)
      : adj_list_(vertex_num),
        matching_(edges_num, -1),
        vertex_count_(vertex_num),
        edges_count_(edges_num) {}

  bool kuhn(int64_t source) {
    if (used_[source]) {
      return false;
    }
    used_[source] = true;
    for (int64_t ind = 0; ind < adj_list_[source].size(); ++ind) {
      int64_t destination = adj_list_[source][ind];
      if (matching_[destination] == -1 || kuhn(matching_[destination])) {
        matching_[destination] = source;
        return true;
      }
    }
    return false;
  }

  void Solve() {
    for (int64_t ind = 0; ind < vertex_count_; ++ind) {
      int64_t vertex;
      std::cin >> vertex;
      while (vertex != 0) {
        adj_list_[ind].push_back(vertex - 1);
        std::cin >> vertex;
      }
    }
    for (int64_t ind = 0; ind < vertex_count_; ++ind) {
      used_.assign(vertex_count_, false);
      kuhn(ind);
    }
    int64_t count = 0;
    for (int64_t ind = 0; ind < edges_count_; ++ind) {
      if (matching_[ind] != -1) {
        ++count;
      }
    }
    std::cout << count << '\n';
    for (int64_t ind = 0; ind < edges_count_; ++ind) {
      if (matching_[ind] != -1) {
        std::cout << matching_[ind] + 1 << " " << ind + 1 << '\n';
      }
    }
  }

 private:
  std::vector<std::vector<int64_t>> adj_list_;
  std::vector<int64_t> matching_;
  std::vector<bool> used_;
  int64_t vertex_count_;
  int64_t edges_count_;
};

int main() {
  int64_t vertex_num;
  int64_t edges_num;
  std::cin >> vertex_num >> edges_num;
  Graph graph(vertex_num, edges_num);
  graph.Solve();

  return 0;
}