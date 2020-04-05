#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <mutex>

#include "mystructs.h"

class Map{

public:
  // public member functions
  Map(std::string pathToGrid);

  void reservePathInMap(std::vector<Position> &path);

  void freeField(Position &pos);

  std::vector<std::vector<State>> getMap();

  Position getRandPos(bool reserve);

  int rowSize() const{return _rowSize;};
  int colSize() const{return _colSize;};

private:
  // private member functions
  std::vector<State> parseLine(std::string line);
  // private member variables
  int _rowSize;
  int _colSize;
  std::vector<std::vector<State>> _map;
  // mutex for save reading and writing to the map
  std::mutex _map_mutex;
};

#endif
