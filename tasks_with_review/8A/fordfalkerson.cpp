#include <iostream>
#include <limits>
#include <vector>

namespace MaxCap {
const int64_t max_cap = std::numeric_limits<int64_t>::max();
}

struct Edge {
  Edge() = default;
  Edge(int64_t source, int64_t destination, int64_t flow, size_t count)
      : source_(source),
        destination_(destination),
        flow_capacity_(flow),
        id_(count),
        flow_(0) {}

  int64_t source_;
  int64_t destination_;
  int64_t flow_capacity_;
  size_t id_;
  int64_t flow_;
};

class Graph {
 public:
  Graph(int64_t verticies)
      : adj_list_(verticies),
        visited_(verticies),
        size_(verticies) {}

  void AddEdge(int64_t source, int64_t destination, int64_t flow) {
    Edge edge(source, destination, flow, adj_list_[destination].size());
    Edge reversed_edge(destination, source, 0, adj_list_[source].size());
    adj_list_[source].push_back(edge);
    adj_list_[destination].push_back(reversed_edge);
    ++edge_count_;
  }

  int64_t DFS(int64_t vertex, int64_t capacity, int64_t drain) {
    if (vertex == drain) {
      return capacity;
    }
    visited_[vertex] = true;
    for (auto& edge : adj_list_[vertex]) {
      int64_t destination = edge.destination_;
      if (!visited_[destination] && edge.flow_ < edge.flow_capacity_) {
        int64_t delta = DFS(
            destination, std::min(capacity, edge.flow_capacity_ - edge.flow_), drain);
        if (delta > 0) {
          edge.flow_ += delta;
          adj_list_[destination][edge.id_].flow_ -= delta;
          return delta;
        }
      }
    }
    return 0;
  }

  void Clear() { visited_.assign(visited_.size(), 0); }

 private:
  std::vector<std::vector<Edge>> adj_list_;
  int64_t size_;
  std::vector<bool> visited_;
  size_t edge_count_ = 0;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  int64_t vertex_num = 0;
  int64_t edges_num = 0;
  std::cin >> vertex_num >> edges_num;
  Graph graph(vertex_num);
  for (int64_t i = 0; i < edges_num; ++i) {
    int64_t source = 0;
    int64_t destination = 0;
    int64_t flow = 0;
    std::cin >> source >> destination >> flow;
    graph.AddEdge(source - 1, destination - 1, flow);
  }
  int64_t val = 0;
  while (true) {
    graph.Clear();
    int64_t delta = graph.DFS(0, MaxCap::max_cap, vertex_num - 1);
    if (delta == 0) {
      break;
    }
    val += delta;
  }
  std::cout << val;
}