#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "graph.hpp"
#include <string>
#include <vector>

class Solution {
public:
  Solution(Graph &g);
  void solve();

private:
  Graph &graph;
  std::string capital;
  std::vector<std::vector<std::string>> sccs;
  std::vector<std::string> secondaryBattalions;
  std::vector<std::vector<std::string>> patrols;
  void defineCapital();
  void defineSecondaryBattalions();
  void definePatrols();
};

#endif // SOLUTION_HPP
