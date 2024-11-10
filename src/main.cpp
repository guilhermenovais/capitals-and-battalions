#include "../include/graph.hpp"
#include "../include/solution.hpp"
#include <iostream>

int main() {
  int numVertices, numEdges;
  std::cin >> numVertices >> numEdges;

  Graph g;

  for (int i = 0; i < numEdges; ++i) {
    std::string from, to;
    std::cin >> from >> to;
    g.addVertex(from);
    g.addVertex(to);
    g.addEdge(from, to);
  }

  Solution solution(g);
  solution.solve();

  return 0;
}
