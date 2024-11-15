#include "../include/graph.hpp"
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

Graph::Graph() : INT_MAX(std::numeric_limits<int>::max()) {}

void removeElement(std::vector<std::string> &vec, std::string value) {
  size_t writeIndex = 0;

  for (size_t readIndex = 0; readIndex < vec.size(); ++readIndex) {
    if (vec[readIndex] != value) {
      vec[writeIndex++] = vec[readIndex];
    }
  }

  vec.resize(writeIndex);
}

bool containsValue(const std::vector<std::string> &vec, std::string value) {
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] == value) {
      return true;
    }
  }
  return false;
}

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

  for (const auto &battalionSccPair : battalionsToScss) {
    const std::string &battalion = battalionSccPair.first;
    const std::vector<std::string> &scc = battalionSccPair.second;

    if (scc.size() <= 1)
      continue;

    std::vector<std::string> patrolRoute = findPatrolInSCC(scc, battalion);

    patrolRoute.pop_back();

    patrols.push_back(patrolRoute);
  }

  return patrols;
}

std::vector<std::string>
Graph::findPatrolInSCC(const std::vector<std::string> &scc,
                       const std::string &startVertex) {
  std::unordered_map<std::string, std::vector<std::string>> localAdjList;

  for (const std::string &vertex : scc) {
    for (const std::string &adjListItem : adjList[vertex]) {
      bool isInScc = false;
      for (const auto &sccMember : scc) {
        if (sccMember == adjListItem) {
          isInScc = true;
          break;
        }
      }
      if (isInScc) {
        localAdjList[vertex].push_back(adjListItem);
      }
    }
  }

  std::vector<std::string> path;

  std::unordered_map<std::string, std::vector<std::string>>
      unvisitedEdgesByVertex;
  unvisitedEdgesByVertex.insert(localAdjList.begin(), localAdjList.end());

  std::string currentVertex = startVertex;
  path.push_back(startVertex);

  int numUnvisitedEdges = 0;
  for (const auto &vertex : unvisitedEdgesByVertex) {
    numUnvisitedEdges += int(vertex.second.size());
  }

  while (numUnvisitedEdges > 0) {
    if (unvisitedEdgesByVertex[currentVertex].size() > 0) {
      std::string next = unvisitedEdgesByVertex[currentVertex].back();
      unvisitedEdgesByVertex[currentVertex].pop_back();
      currentVertex = next;
      numUnvisitedEdges--;
      path.push_back(next);
    } else {
      std::string vertexWithUnvisitedEdge;
      for (const auto &vertex : unvisitedEdgesByVertex) {
        if (vertex.second.size() > 0) {
          vertexWithUnvisitedEdge = vertex.first;
          break;
        }
      }
      std::vector<std::string> pathToVertex = getShortestPathBetween(
          currentVertex, vertexWithUnvisitedEdge, localAdjList);
      int sizePathToVertex = int(pathToVertex.size());
      for (int i = 1; i < sizePathToVertex; i++) {
        std::string sourceVertex = pathToVertex[i];
        path.push_back(sourceVertex);
        if (i < sizePathToVertex - 1) {
          std::string destVertex = pathToVertex[i + 1];
          if (containsValue(unvisitedEdgesByVertex[sourceVertex], destVertex)) {
            removeElement(unvisitedEdgesByVertex[sourceVertex], destVertex);
            numUnvisitedEdges--;
          }
        }
      }
      currentVertex = vertexWithUnvisitedEdge;
    }
  }

  if (currentVertex != startVertex) {
    std::vector<std::string> pathToVertex =
        getShortestPathBetween(currentVertex, startVertex, localAdjList);
    path.insert(path.end(), pathToVertex.begin() + 1, pathToVertex.end());
  }

  return path;
}

std::vector<std::string> Graph::getShortestPathBetween(
    std::string from, std::string to,
    std::unordered_map<std::string, std::vector<std::string>> adjList) {

  std::unordered_map<std::string, bool> visited;

  std::unordered_map<std::string, std::string> parent;

  std::queue<std::string> queue;

  queue.push(from);
  visited[from] = true;
  parent[from] = "";

  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();

    if (current == to)
      break;

    for (const std::string &neighbor : adjList.at(current)) {
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        parent[neighbor] = current;
        queue.push(neighbor);
      }
    }
  }

  if (!visited[to]) {
    return {};
  }

  std::vector<std::string> path;
  for (std::string at = to; at != ""; at = parent[at]) {
    path.push_back(at);
  }

  std::reverse(path.begin(), path.end());

  return path;
}
