#include "../include/graph.hpp"
#include <limits>
#include <queue>

Graph::Graph() : INT_MAX(std::numeric_limits<int>::max()) {}

void Graph::addVertex(const std::string &name) {
  if (adjList.find(name) == adjList.end()) {
    adjList[name] = std::vector<std::string>();
    adjListReversed[name] = std::vector<std::string>();
  }
}

void Graph::addEdge(const std::string &from, const std::string &to) {
  adjList[from].push_back(to);
  adjListReversed[to].push_back(from);
}

std::string Graph::findCapital() {
  std::string bestCapital = "";
  int minDistanceSum = INT_MAX;

  for (const auto &entry : adjList) {
    const std::string &capitalCandidate = entry.first;

    std::unordered_map<std::string, int> distances =
        calculateShortestPaths(capitalCandidate);

    int distanceSum = 0;
    bool canReachAll = true;

    for (const auto &d : adjList) {
      const std::string &target = d.first;
      if (distances[target] == INT_MAX) {
        canReachAll = false;
        break;
      }
      distanceSum += distances[target];
    }

    if (canReachAll && distanceSum < minDistanceSum) {
      minDistanceSum = distanceSum;
      bestCapital = capitalCandidate;
    }
  }

  return bestCapital;
}

void Graph::DFS(const std::string &v,
                std::unordered_map<std::string, bool> &visited,
                std::vector<std::string> &finishStack) {
  visited[v] = true;

  for (const std::string &neighbor : adjList[v]) {
    if (!visited[neighbor]) {
      DFS(neighbor, visited, finishStack);
    }
  }

  finishStack.push_back(v);
}

void Graph::reverseDFS(const std::string &v,
                       std::unordered_map<std::string, bool> &visited,
                       std::vector<std::string> &component) {
  visited[v] = true;
  component.push_back(v);

  for (const std::string &neighbor : adjListReversed[v]) {
    if (!visited[neighbor]) {
      reverseDFS(neighbor, visited, component);
    }
  }
}

std::vector<std::vector<std::string>> Graph::findSCCs() {
  std::vector<std::string> finishStack;
  std::unordered_map<std::string, bool> visited;

  for (const auto &vertex : adjList) {
    visited[vertex.first] = false;
  }

  for (const auto &vertex : adjList) {
    if (!visited[vertex.first]) {
      DFS(vertex.first, visited, finishStack);
    }
  }

  for (const auto &vertex : adjList) {
    visited[vertex.first] = false;
  }

  std::vector<std::vector<std::string>> sccs;

  while (!finishStack.empty()) {
    std::string vertex = finishStack.back();
    finishStack.pop_back();

    if (!visited[vertex]) {
      std::vector<std::string> component;
      reverseDFS(vertex, visited, component);
      sccs.push_back(component);
    }
  }

  return sccs;
}

std::unordered_map<std::string, int>
Graph::calculateShortestPaths(const std::string &start) {
  std::unordered_map<std::string, int> distance;

  for (const auto &pair : adjList) {
    distance[pair.first] = INT_MAX;
  }

  std::queue<std::string> q;
  q.push(start);
  distance[start] = 0;

  while (!q.empty()) {
    std::string u = q.front();
    q.pop();

    for (const std::string &neighbor : adjList[u]) {
      if (distance[neighbor] == INT_MAX) {
        distance[neighbor] = distance[u] + 1;
        q.push(neighbor);
      }
    }
  }

  return distance;
}
