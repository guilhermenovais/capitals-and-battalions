#include "../include/solution.hpp"
#include <iostream>

Solution::Solution(Graph &g) : graph(g) {}

void Solution::solve() {
  defineCapital();
  defineSecondaryBattalions();
}

void Solution::defineCapital() {
  capital = graph.findCapital();
  std::cout << capital << std::endl;
}

void Solution::defineSecondaryBattalions() {
  secondaryBattalions = graph.findSecondaryBattalions();
  std::cout << secondaryBattalions.size() << std::endl;
  for (const std::string &battalion : secondaryBattalions) {
    std::cout << battalion << std::endl;
  }
}
