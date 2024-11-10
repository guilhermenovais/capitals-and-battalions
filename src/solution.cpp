#include "../include/solution.hpp"
#include <algorithm>
#include <iostream>

Solution::Solution(Graph &g) : graph(g) {}

void Solution::solve() {
  defineCapital();
  sccs = graph.findSCCs();
  defineSecondaryBattalions();
}

void Solution::defineCapital() {
  capital = graph.findCapital();
  std::cout << capital << std::endl;
}

void Solution::defineSecondaryBattalions() {
  long unsigned int numSecondaryBattalions = sccs.size() - 1;
  std::cout << numSecondaryBattalions << std::endl;
  if (numSecondaryBattalions > 0) {
    for (const auto &scc : sccs) {
      if (std::find(scc.begin(), scc.end(), capital) == scc.end()) {
        for (const std::string &vertex : scc) {
          std::cout << vertex << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}
