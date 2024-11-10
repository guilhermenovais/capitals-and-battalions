#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "graph.hpp"
#include <string>
#include <vector>

/**
 * @class Solution
 * @brief Classe responsável por proporcionar uma solução para o problema de
 * determinar a capital, os batalhões secundários e realizar os patrulhamentos
 * em um grafo.
 */
class Solution {
public:
  /**
   * @brief Construtor da classe Solution.
   * Inicializa a solução a partir de um grafo fornecido.
   * @param g Referência para o objeto da classe Graph que representa o grafo.
   */
  Solution(Graph &g);

  /**
   * @brief Método principal para resolver o problema.
   * Essa função invoca os métodos apropriados para determinar a capital, os
   * batalhões secundários, e definir os patrulhamentos no grafo.
   */
  void solve();

private:
  Graph &graph; ///< Referência ao grafo que será utilizado para encontrar a
                ///< solução.
  std::string capital; ///< Nome da capital identificada no grafo.
  std::vector<std::vector<std::string>>
      sccs; ///< Lista de componentes fortemente conectados (SCCs).
  std::vector<std::string>
      secondaryBattalions; ///< Lista de batalhões secundários para os SCCs.
  std::vector<std::vector<std::string>>
      patrols; ///< Lista com os patrulhamentos definidos nos SCCs.

  /**
   * @brief Define a capital do grafo.
   * Chama o método apropriado no grafo para encontrar o vértice que atua como
   * capital.
   */
  void defineCapital();

  /**
   * @brief Define os batalhões secundários para os SCCs.
   * Para cada SCC, a função identifica o vértice mais adequado para ser o
   * batalhão (mais próximo da capital).
   */
  void defineSecondaryBattalions();

  /**
   * @brief Define os patrulhamentos em cada SCC.
   * Define os caminhos de patrulhamento iniciando nos batalhões e garantindo
   * que todas as rotas sejam cobertas.
   */
  void definePatrols();
};

#endif // SOLUTION_HPP
