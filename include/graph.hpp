#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <unordered_map>
#include <vector>

class Graph {
public:
  Graph();
  void addVertex(const std::string &name);
  void addEdge(const std::string &from, const std::string &to);
  std::string findCapital();
  std::vector<std::vector<std::string>> findSCCs();
  std::vector<std::string> findSecondaryBattalions();

private:
  const int INT_MAX;
  std::unordered_map<std::string, std::vector<std::string>> adjList;
  std::unordered_map<std::string, std::vector<std::string>> adjListReversed;
  void DFS(const std::string &v, std::unordered_map<std::string, bool> &visited,
           std::vector<std::string> &finishStack);
  void reverseDFS(const std::string &v,
                  std::unordered_map<std::string, bool> &visited,
                  std::vector<std::string> &component);
  int calculateSCCInternalDistances(const std::vector<std::string> &scc,
                                    const std::string &vertex);
  std::unordered_map<std::string, int>
  calculateShortestPaths(const std::string &start);
};

#endif // GRAPH_HPP
