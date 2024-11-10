#include "../include/solution.hpp"
#include <iostream>
#include <ostream>
#include <vector>

Solution::Solution(Graph &g) : graph(g) {}

void Solution::solve() {
  defineCapital();
  defineSecondaryBattalions();
  definePatrols();
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

void Solution::definePatrols() {
  patrols = graph.definePatrols();
  std::cout << patrols.size() << std::endl;
  for (const std::vector<std::string> &patrol : patrols) {
    for (const std::string &urbaneCenter : patrol) {
      std::cout << urbaneCenter << " ";
    }
    std::cout << std::endl;
  }
}
