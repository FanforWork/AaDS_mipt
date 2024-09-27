#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

namespace HighVal {
const uint64_t kMax = std::numeric_limits<uint64_t>::max();
const uint64_t kLim = 2009000999;
};  // namespace HighVal

template <class Vertex>
struct Edge {
  Edge(const Vertex& source, const Vertex& destination, uint64_t weight)
      : source_(source), destination_(destination), weight_(weight) {}

  const Vertex& GetSource() const { return source_; }
  const Vertex& GetDestination() const { return destination_; }
  const Vertex& GetWeight() const { return weight_; }

 private:
  Vertex source_;
  Vertex destination_;
  uint64_t weight_;
};

struct CompareDistance {
  bool operator()(const std::pair<uint64_t, uint64_t>& lhs,
                  const std::pair<uint64_t, uint64_t>& rhs) const {
    return lhs.first > rhs.first;
  }
};

/// decomposed Djikstra
template <class Graph, class Visitor>
void Djikstra(Graph& graph, const typename Graph::VertexT& start,
              Visitor& visitor) {
  std::priority_queue<std::pair<uint64_t, uint64_t>,
                      std::vector<std::pair<uint64_t, uint64_t>>,
                      CompareDistance>
      heap;
  std::vector<bool> visited(graph.GetVericiesCount(), false);
  visitor.ChangeDist(start, 0);
  heap.push({0, start});
  ProcessDijkstra(graph, visitor, heap, visited);
}

template <class Graph, class Visitor>
void ProcessDijkstra(
    Graph& graph, Visitor& visitor,
    std::priority_queue<std::pair<uint64_t, uint64_t>,
                        std::vector<std::pair<uint64_t, uint64_t>>,
                        CompareDistance>& heap,
    std::vector<bool>& visited) {
  while (!heap.empty()) {
    auto current_dist = heap.top().first;
    auto source = heap.top().second;
    heap.pop();
    if (visited[source]) {
      continue;
    }
    visited[source] = true;
    if (current_dist == HighVal::kMax) {
      break;
    }
    RelaxEdges(graph, visitor, heap, source, current_dist);
  }
}

template <class Graph, class Visitor>
void RelaxEdges(Graph& graph, Visitor& visitor,
                std::priority_queue<std::pair<uint64_t, uint64_t>,
                                    std::vector<std::pair<uint64_t, uint64_t>>,
                                    CompareDistance>& heap,
                typename Graph::VertexT& source, uint64_t current_dist) {
  for (const auto& edge : graph.GetOutgoingEdges(source)) {
    const auto& destination = edge.GetDestination();
    const auto& length = edge.GetWeight();
    if (visitor.GetDistance(destination) <= current_dist + length) {
      continue;
    }
    visitor.ChangeDist(destination, current_dist + length);
    heap.push({visitor.GetDistance(destination), destination});
  }
}

//////////////
template <class Graph>
class AbstractBFSVisitor {
 public:
  virtual void DiscoverEdge(const Graph::EdgeT& vertex) = 0;
  virtual ~AbstractBFSVisitor() = default;
};

template <class Graph>
class ShortestPathsVisitor : AbstractBFSVisitor<Graph> {
 public:
  using VertexT = Graph::VertexT;

  ShortestPathsVisitor(Graph& graph)
      : distance_(graph.GetVericiesCount(), HighVal::kMax) {}

  void DiscoverEdge(const Graph::EdgeT& edge) override {
    ancestors_[edge.GetDestination()] = edge.GetSource();
  }

  uint64_t GetDistance(uint64_t index) { return distance_[index]; }

  void ChangeDist(uint64_t index, uint64_t value) { distance_[index] = value; }

  void ClearDist() { distance_.clear(); }

  uint64_t DistSize() { return distance_.size(); }

 private:
  std::unordered_map<VertexT, VertexT> ancestors_;
  std::vector<uint64_t> distance_;
};

template <typename Vertex = uint64_t, typename Edges = Edge<uint64_t>>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge<VertexT>;

  Graph(uint64_t vertices) : adj_list_(vertices), size_(vertices) {}

  uint64_t GetVericiesCount() { return size_; }

  uint64_t GetEdgesCount() { return edge_count_; }

  void MakeGraph() {
    uint64_t coridors = 0;
    uint64_t start = 0;
    std::cin >> coridors;
    for (uint64_t i = 0; i < coridors; ++i) {
      uint64_t source;
      uint64_t destination;
      uint64_t lenth;
      std::cin >> source >> destination >> lenth;
      AddEdge(source, destination, lenth);
    }
    std::cin >> start;
    AddStart(start);
  }

  uint64_t GetStart() { return start_; }

  const std::vector<Edge<VertexT>>& GetOutgoingEdges(const VertexT& vertex) {
    return adj_list_[vertex];
  }

 private:
  void AddStart(uint64_t start) { start_ = start; }

  void AddEdge(uint64_t source, uint64_t destination, uint64_t lenth) {
    Edge edge(source, destination, lenth);
    Edge reversed_edge(destination, source, lenth);
    adj_list_[source].push_back(edge);
    adj_list_[destination].push_back(reversed_edge);
    ++edge_count_;
  }

  uint64_t edge_count_{0};
  std::vector<std::vector<Edge<VertexT>>> adj_list_;
  uint64_t size_;
  uint64_t start_;
};

template <typename Graph>
void ComputeShortestPaths(Graph& graph, ShortestPathsVisitor<Graph>& visitor) {
  Djikstra(graph, graph.GetStart(), visitor);
}

template <typename Graph>
void OutputShortestPaths(ShortestPathsVisitor<Graph>& visitor) {
  for (uint64_t j = 0; j < visitor.DistSize(); ++j) {
    if (visitor.GetDistance(j) != HighVal::kMax) {
      std::cout << visitor.GetDistance(j) << ' ';
    } else {
      std::cout << HighVal::kLim << ' ';
    }
  }
  visitor.ClearDist();
  std::cout << '\n';
}

void SolveAndOutup(uint64_t map_count) {
  for (uint64_t ind = 0; ind < map_count; ++ind) {
    uint64_t rooms = 0;
    std::cin >> rooms;
    Graph graph(rooms);
    graph.MakeGraph();
    ShortestPathsVisitor<Graph<uint64_t>> visitor(graph);
    ComputeShortestPaths(graph, visitor);
    OutputShortestPaths(visitor);
  }
}

void Optimise() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  Optimise();
  uint64_t map_count = 0;
  std::cin >> map_count;
  SolveAndOutup(map_count);
}
