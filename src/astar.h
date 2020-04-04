#include <algorithm>  // for sort
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "mystructs.h"

class AStar{

public:
  /**
   * Implementation of A* search algorithm
   */
  bool Search(std::vector<std::vector<State>> grid, std::vector<std::vector<Position>> &path, int init[2], int goal[2]);

private:
  /**
   * Sort the two-dimensional vector of ints in descending order.
   */
  void CellSort(std::vector<std::vector<int>> *v);
  // Calculate the manhattan distance
  int Heuristic(int x1, int y1, int x2, int y2);
  /**
   * Check that a cell is valid: on the grid, not an obstacle, and clear.
   */
  bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid);
  /**
   * Add a node to the open list and mark it as open.
   */
  void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid, int x_pre, int y_pre);
  /**
   * Expand current nodes's neighbors and add them to the open list.
   */
  void ExpandNeighbors(const std::vector<int> &current, int goal[2], std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid);
};
