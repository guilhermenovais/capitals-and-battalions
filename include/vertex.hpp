#include <limits>
#include <string>

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex {
public:
  int id;
  std::string name;
  int distToCapital;
  bool visited;

  Vertex(int vertexId, const std::string vertexName);
};

#endif // VERTEX_HPP
