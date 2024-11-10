#include "../include/vertex.hpp"

Vertex::Vertex(int vertexId, const std::string vertexName) {
  const int INT_MAX = std::numeric_limits<int>::max();
  id = vertexId;
  name = vertexName;
  visited = false;
  distToCapital = INT_MAX;
}
