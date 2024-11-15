#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class Graph
 * @brief Representa um grafo direcionado com operações relacionadas à definição
 * de capital, componentes fortemente conectados (SCCs), batalhões e
 * patrulhamentos.
 */
class Graph {
public:
  /**
   * @brief Construtor padrão da classe Graph.
   * Inicializa o grafo sem vértices nem arestas.
   */
  Graph();

  /**
   * @brief Adiciona um vértice ao grafo.
   * Se o vértice já existe, não faz nada.
   * @param name Nome do vértice a ser adicionado.
   */
  void addVertex(const std::string &name);

  /**
   * @brief Adiciona uma aresta direcionada entre dois vértices no grafo.
   * Se os vértices de origem e/ou destino não existirem, eles também são
   * adicionados ao grafo.
   * @param from Nome do vértice de origem.
   * @param to Nome do vértice de destino.
   */
  void addEdge(const std::string &from, const std::string &to);

  /**
   * @brief Encontra a capital do grafo.
   * A capital é definida como o vértice que consegue alcançar todos os outros
   * vértices com o menor somatório de distâncias.
   * @return Nome do vértice escolhido como capital.
   */
  std::string findCapital();

  /**
   * @brief Encontra os Componentes Fortemente Conectados (SCCs) no grafo.
   * Utiliza o algoritmo de Kosaraju para encontrar componentes fortemente
   * conectados.
   * @return Um vetor contendo os SCCs, onde cada SCC é um vetor de nomes de
   * vértices.
   */
  std::vector<std::vector<std::string>> findSCCs();

  /**
   * @brief Determina os batalhões secundários para cada SCC que não contenha a
   * capital. Escolhe, para cada SCC, o vértice mais próximo da capital como
   * batalhão secundário.
   * @return Um vetor com os nomes dos batalhões secundários.
   */
  std::vector<std::string> findSecondaryBattalions();

  /**
   * @brief Define os patrulhamentos possíveis para todos os SCCs que contêm
   * batalhões. Para cada SCC, realiza um patrulhamento, passando por todas as
   * arestas.
   * @return Um vetor de patrulhamentos, cada um representado por um vetor de
   * nomes de vértices.
   */
  std::vector<std::vector<std::string>> definePatrols();

private:
  const int INT_MAX; ///< Constante para representar a distância infinita.

  std::unordered_map<std::string, std::vector<std::string>>
      adjList; ///< Lista de adjacência do grafo.
  std::unordered_map<std::string, std::vector<std::string>>
      adjListReversed; ///< Lista de adjacência reversa usada pelos algoritmos.

  /**
   * @brief Realiza um DFS no grafo original para encontrar a ordem de
   * finalização dos vértices.
   * @param v Vértice atual.
   * @param visited Mapa para rastrear vértices visitados.
   * @param finishStack Vetor em que os vértices serão armazenados na ordem de
   * finalização.
   */
  void DFS(const std::string &v, std::unordered_map<std::string, bool> &visited,
           std::vector<std::string> &finishStack);

  /**
   * @brief Realiza um DFS no grafo reverso para encontrar componentes
   * fortemente conectados (SCCs).
   * @param v Vértice atual.
   * @param visited Mapa para rastrear vértices visitados.
   * @param component Vetor que armazena os vértices do SCC atual.
   */
  void reverseDFS(const std::string &v,
                  std::unordered_map<std::string, bool> &visited,
                  std::vector<std::string> &component);

  /**
   * @brief Calcula a soma das distâncias de um vértice para todos os outros
   * vértices de um SCC.
   * @param scc Vetor contendo os vértices do SCC.
   * @param vertex Vértice de referência para o cálculo.
   * @return Soma das distâncias do vértice para os outros vértices do SCC.
   */
  int calculateSCCInternalDistances(const std::vector<std::string> &scc,
                                    const std::string &vertex);

  /**
   * @brief Calcula as distâncias mínimas do vértice inicial para todos os
   * outros vértices do grafo. Utiliza a busca em largura (BFS).
   * @param start Vértice inicial.
   * @return Mapa com as menores distâncias do vértice `start` para cada vértice
   * acessível.
   */
  std::unordered_map<std::string, int>
  calculateShortestPaths(const std::string &start);

  /**
   * @brief Encontra um caminho de patrulhamento em um SCC.
   * Garante que todas as arestas do SCC sejam percorridas.
   * @param scc Vetor contendo os vértices do SCC.
   * @param startVertex Vértice de início (o batalhão).
   * @return Um vetor de pares `{from, to}` representando o caminho percorrido.
   */
  std::vector<std::string> findPatrolInSCC(const std::vector<std::string> &scc,
                                           const std::string &startVertex);

  /**
   * @brief Função que encontra o menor caminho entre dois vértices em um grafo
   * não ponderado. Utiliza busca em largura (BFS) para encontrar o menor
   * caminho em termos de número de arestas.
   * @param from Vértice de origem.
   * @param to Vértice de destino.
   * @param adjList Lista de adjacências que representa o grafo.
   * @return Um vetor que contém os vértices no menor caminho de `from` para
   * `to`. Se não houver caminho, o vetor será vazio.
   */
  std::vector<std::string> getShortestPathBetween(
      std::string from, std::string to,
      std::unordered_map<std::string, std::vector<std::string>> adjList);

  std::string
      capital; ///< Nome da capital do grafo, definida na função `findCapital`.
  std::unordered_map<std::string, std::vector<std::string>>
      battalionsToScss; ///< Mapeia os batalhões com seus respectivos SCCs.
};

#endif // GRAPH_HPP
