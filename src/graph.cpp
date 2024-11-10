#include "../include/graph.hpp"
#include <limits>
#include <queue>
#include <stack>

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

int Graph::calculateSCCInternalDistances(const std::vector<std::string> &scc,
                                         const std::string &vertex) {
  std::unordered_map<std::string, int> distances =
      calculateShortestPaths(vertex);
  int sum = 0;

  for (const std::string &other : scc) {
    sum += distances[other];
  }

  return sum;
}

std::vector<std::string> Graph::findSecondaryBattalions() {
  std::vector<std::string> secondaryBattalions;
  std::string capital = findCapital();
  std::unordered_map<std::string, int> distancesToCapital =
      calculateShortestPaths(capital);

  auto sccs = findSCCs();

  for (const auto &scc : sccs) {
    bool containsCapital = false;
    for (const auto &v : scc) {
      if (v == capital) {
        containsCapital = true;
        battalionsToScss[capital] = scc;
        break;
      }
    }
    if (containsCapital) {
      continue;
    }

    std::string bestBattalion;
    int minDistanceToCapital = INT_MAX;
    int minInternalDistanceSum = INT_MAX;

    for (const auto &vertex : scc) {
      int distanceToCapital = distancesToCapital[vertex];

      if (distanceToCapital < minDistanceToCapital) {
        minDistanceToCapital = distanceToCapital;
        bestBattalion = vertex;
        minInternalDistanceSum = calculateSCCInternalDistances(scc, vertex);
      } else if (distanceToCapital == minDistanceToCapital) {
        int internalSum = calculateSCCInternalDistances(scc, vertex);
        if (internalSum < minInternalDistanceSum) {
          bestBattalion = vertex;
          minInternalDistanceSum = internalSum;
        }
      }
    }
    battalionsToScss[bestBattalion] = scc;
    secondaryBattalions.push_back(bestBattalion);
  }

  return secondaryBattalions;
}

std::vector<std::vector<std::string>> Graph::definePatrols() {
  std::vector<std::vector<std::string>> patrols;
  return patrols;
}

std::vector<std::pair<std::string, std::string>>
Graph::findPatrolInSCC(const std::vector<std::string> &scc,
                       const std::string &startVertex) {
  std::unordered_map<std::string, std::vector<std::string>> localAdjList;

  for (const std::string &vertex : scc) {
    localAdjList[vertex] = adjList[vertex];
  }

  std::stack<std::string> stack;
  std::vector<std::pair<std::string, std::string>> patrolRoute;

  stack.push(startVertex);

  while (!stack.empty()) {
    std::string u = stack.top();

    if (!localAdjList[u].empty()) {
      std::string v = localAdjList[u].back();
      localAdjList[u].pop_back();
      stack.push(v);
      patrolRoute.push_back({u, v});
    } else {
      stack.pop();
    }
  }

  patrolRoute.push_back({patrolRoute.back().second, startVertex});
  return patrolRoute;
}
