#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

enum class Colors { KWhite = 0, KGray, KBlack };

template <class Vertex>
struct Edge {
  Edge(const Vertex& source, const Vertex& destination)
      : source_(source), destination_(destination) {}

  const Vertex& GetSource() const { return source_; }
  Vertex& GetSource() { return source_; }
  const Vertex& GetDestination() const { return destination_; }
  Vertex& GetDestination() { return destination_; }

 private:
  Vertex source_;
  Vertex destination_;
};

template <class Graph, class Visitor>
void DFS(Graph& graph, const typename Graph::VertexT& vertex,
         std::unordered_map<typename Graph::VertexT, Colors>& colors,
         Visitor visitor) {
  colors[vertex] = Colors::KGray;
  visitor.DiscoverVertex(vertex);
  for (const auto& outgoing_edge : graph.GetOutgoingEdges(vertex)) {
    const auto& neighbour = outgoing_edge.GetDestination();
    if (GetColor<Graph>(neighbour, colors) == Colors::KWhite) {
      DFS(graph, neighbour, colors, visitor);
    }
  }
  colors[vertex] = Colors::KBlack;
  visitor.FinishVertex(vertex);
}

template <class Graph>
class AbstractDFSVisitor {
 public:
  virtual void DiscoverVertex(const Graph::VertexT& vertex) = 0;
  virtual void FinishVertex(const Graph::VertexT& vertex) = 0;
  virtual ~AbstractDFSVisitor() = default;
};

template <class Graph>
class TimerDFSVisitor : public AbstractDFSVisitor<Graph> {
 public:
  TimerDFSVisitor(
      std::vector<typename Graph::VertexT>& component,
      std::unordered_map<typename Graph::VertexT, int32_t>& visit_vertex_time,
      std::unordered_map<typename Graph::VertexT, int32_t>& leave_vertex_time)
      : component_(component),
        visit_vertex_time_(visit_vertex_time),
        leave_vertex_time_(leave_vertex_time) {}

  void DiscoverVertex(const Graph::VertexT& vertex) final {
    AddToComponent(vertex + 1);
    ++time_;
    visit_vertex_time_[vertex] = time_;
  }

  void FinishVertex(const Graph::VertexT& vertex) final {
    ++time_;
    leave_vertex_time_[vertex] = time_;
  }

  virtual ~TimerDFSVisitor() = default;

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;

  void AddToComponent(const Graph::VertexT& vertex) {
    component_.push_back(vertex);
  }

  int32_t time_ = 0;
  std::vector<typename Graph::VertexT>& component_;
  std::unordered_map<typename Graph::VertexT, int32_t>& visit_vertex_time_;
  std::unordered_map<typename Graph::VertexT, int32_t>& leave_vertex_time_;
};

template <typename Vertex = int32_t, typename Edges = Edge<int32_t>>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge<VertexT>;

  Graph(uint64_t vertices) : adj_list_(vertices) {}

  void MakeGraph(uint64_t pairs, Edge<VertexT> edge) {
    for (uint64_t index = 0; index < pairs; ++index) {
      std::cin >> edge.GetSource() >> edge.GetDestination();
      AddEdge(edge.GetSource() - 1, edge.GetDestination() - 1);
    }
  }

  Graph(const std::vector<Edge<VertexT>>& edges) {
    for (const auto& edge : edges) {
      adj_list_[edge.GetSource()].push_back(edge);
    }
  }

  uint64_t GetVericiesCount() { return adj_list_.size(); }

  uint64_t GetEdgesCount() { return edge_count_; }

  const std::vector<Edge<VertexT>>& GetOutgoingEdges(const VertexT& vertex) {
    return adj_list_[vertex];
  }

 private:
  void AddEdge(VertexT source, VertexT destination) {
    Edge edge(source, destination);
    Edge reversed_edge(destination, source);
    adj_list_[source].push_back(edge);
    adj_list_[destination].push_back(reversed_edge);
    ++edge_count_;
  }

  int64_t edge_count_{0};
  std::vector<std::vector<Edge<VertexT>>> adj_list_;
};

void PrintComponents(
    const std::vector<std::vector<int32_t>>& connective_components) {
  std::cout << connective_components.size() << '\n';
  for (const auto& team : connective_components) {
    std::cout << team.size() << '\n';
    for (int32_t edge : team) {
      std::cout << edge << ' ';
    }
    std::cout << '\n';
  }
}
template <typename Graph>
Colors GetColor(const typename Graph::VertexT& vertex,
                std::unordered_map<typename Graph::VertexT, Colors>& colors) {
  if (colors.contains(vertex)) {
    return colors[vertex];
  }
  return Colors::KWhite;
}

template <typename Graph>
std::vector<std::vector<typename Graph::VertexT>> FindConnectiveComponents(
    Graph& graph) {
  std::unordered_map<typename Graph::VertexT, Colors> colors;
  std::vector<std::vector<typename Graph::VertexT>> connective_components;
  std::unordered_map<typename Graph::VertexT, int32_t> visit_vertex_time;
  std::unordered_map<typename Graph::VertexT, int32_t> leave_vertex_time;
  for (uint64_t i = 0; i < graph.GetVericiesCount(); ++i) {
    if (GetColor<Graph>(i, colors) == Colors::KWhite) {
      std::vector<typename Graph::VertexT> component;
      TimerDFSVisitor<Graph> visitor(component, visit_vertex_time,
                                     leave_vertex_time);
      DFS(graph, i, colors, visitor);
      if (!component.empty()) {
        connective_components.push_back(std::move(component));
      }
    }
  }
  return connective_components;
}

int main() {
  uint64_t vertex_num = 0;
  uint64_t edges_num = 0;
  std::cin >> vertex_num >> edges_num;
  Edge edge(0, 0);
  Graph graph(vertex_num);
  graph.MakeGraph(edges_num, edge);
  std::vector<std::vector<int32_t>> connective_components =
      FindConnectiveComponents<Graph<int32_t>>(graph);
  PrintComponents(connective_components);
  return 0;
}
