#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

template <class Vertex>
struct Edge {
  Edge() = default;

  Edge(const Vertex& first, const Vertex& second, uint64_t weight)
      : source(first), destination(second), weight(weight) {}

  bool operator<(Edge const& other) const { return weight < other.weight; }

  const Vertex& GetSource() const { return source; }
  const Vertex& GetDestination() const { return destination; }
  const Vertex& GetWeight() const { return weight; }

  Vertex source;
  Vertex destination;
  uint64_t weight;
};

template <typename Vertex = uint64_t, typename Edges = Edge<uint64_t>>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge<VertexT>;

  Graph(uint64_t size) : vert_count_(size), parent_(size), rank_(size, 0) {}

  void MakeGraph() {
    uint64_t edge_count = 0;
    std::cin >> edge_count;
    for (uint64_t ind = 0; ind < edge_count; ++ind) {
      uint64_t source = 0;
      uint64_t destination = 0;
      uint64_t weight;
      std::cin >> source >> destination >> weight;
      AddEdge(source - 1, destination - 1, weight);
    }
  }

  const std::vector<Edge<VertexT>>& GetOutgoingEdges() const {
    return adj_list_;
  }

  std::vector<Edge<VertexT>>& GetOutgoingEdges() { return adj_list_; }

  const std::vector<Edge<VertexT>>& GetGraph() const { return adj_list_; }

  std::vector<Edge<VertexT>>& GetGraph() { return adj_list_; }

  const std::vector<uint64_t>& GetParent() const { return parent_; }

  std::vector<uint64_t>& GetParent() { return parent_; }

  const std::vector<uint64_t>& GetRank() const { return rank_; }

  std::vector<uint64_t>& GetRank() { return rank_; }

  uint64_t GetVertexCount() { return vert_count_; }

  uint64_t GetEdgeCount() { return adj_list_.size(); }

 private:
  void AddEdge(uint64_t source, uint64_t destination, uint64_t weight) {
    Edge edge(source, destination, weight);
    Edge reversed_edge(destination, source, weight);
    adj_list_.push_back(edge);
    adj_list_.push_back(reversed_edge);
  }

  std::vector<Edge<VertexT>> adj_list_;
  uint64_t vert_count_;
  std::vector<uint64_t> parent_;
  std::vector<uint64_t> rank_;
};

template <typename Graph>
uint64_t Find(Graph& graph, uint64_t vert) {
  return (vert == graph.GetParent()[vert])
             ? vert
             : (graph.GetParent()[vert] = Find(graph, graph.GetParent()[vert]));
}

template <typename Graph>
void Union(Graph& graph, uint64_t source, uint64_t destination) {
  source = Find(graph, source);
  destination = Find(graph, destination);
  // if (std::rand() & 1) {
  //   std::swap(source, destination);
  // }
  // if (source != destination) {
  //   graph.GetParent()[source] = destination;
  // }
  if (source != destination) {
    if (graph.GetRank()[source] < graph.GetRank()[destination]) {
      std::swap(source, destination);
    }
    graph.GetParent()[destination] = source;
    if (graph.GetRank()[source] == graph.GetRank()[destination]) {
      ++graph.GetRank()[source];
    }
  }
}

template <typename Graph>
uint64_t GetMinCost(Graph& graph) {
  uint64_t cost = 0;
  std::vector<Edge<typename Graph::VertexT>> result;
  std::sort(graph.GetGraph().begin(), graph.GetGraph().end(),
            [](const Edge<typename Graph::VertexT>& source,
               const Edge<typename Graph::VertexT>& destination) {
              return source < destination;
            });
  for (uint64_t ind = 0; ind < graph.GetParent().size(); ++ind) {
    graph.GetParent()[ind] = ind;
  }
  for (const auto& edge : graph.GetOutgoingEdges()) {
    if (Find(graph, edge.GetSource()) != Find(graph, edge.GetDestination())) {
      cost += edge.GetWeight();
      result.push_back(edge);
      Union(graph, edge.GetSource(), edge.GetDestination());
    }
  }
  return cost;
}

int main() {
  uint64_t vert_count = 0;
  std::cin >> vert_count;
  Graph graph(vert_count);
  graph.MakeGraph();
  uint64_t mst_weight = GetMinCost(graph);
  std::cout << mst_weight << '\n';
}
