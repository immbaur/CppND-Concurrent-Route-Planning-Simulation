#ifndef MAPHANDLE_H
#define MAPHANDLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "mystructs.h"

class Map{

public:

  Map(std::string path){
    std::lock_guard<std::mutex> lck(_map_mutex);
    _map.clear();
    std::ifstream myfile (path);
    if (myfile) {
      std::string line;
      while (getline(myfile, line)) {
        std::vector<State> row = parseLine(line);
        _map.push_back(row);
      }
    } else {
      std::cerr << "File not found!" << std::endl;
    }
    // set the row size and column size of the map
    rowSize = _map.size();
    colSize = _map[1].size();
  };

  void reservePathInMap(std::vector<Position> &path){
    // std::cout << "reserve Path:" << std::endl;
    std::lock_guard<std::mutex> lck(_map_mutex);
    for(auto it = path.begin(); it != path.end(); ++it) {
      _map[(*it).y][(*it).x] = State::kClosed;
      // std::cout << "X: " << (*it).x << "Y: " << (*it).y << std::endl;
    }
  }

  void freeField(Position &pos){
    std::lock_guard<std::mutex> lck(_map_mutex);
    _map[pos.y][pos.x] = State::kEmpty;
    // std::cout << "Free field X: " << pos.x << "Y: " << pos.y << std::endl;
  }

  std::vector<std::vector<State>> getMap(){
    std::lock_guard<std::mutex> lck(_map_mutex);
    std::vector<std::vector<State>> temp = _map;
    return std::move(temp);
  };

  Position getRandPos(bool reserve){
    State state = State::kObstacle;
    Position pos;
    std::lock_guard<std::mutex> lck(_map_mutex);
    while (state != State::kEmpty){
      pos.x = rand()%colSize;
      pos.y = rand()%rowSize;
      state = _map[pos.y][pos.x];
    }
    if(reserve)
      _map[pos.y][pos.x] = State::kClosed;
    return pos;
  }
  // publick memeber variables
  int rowSize;
  int colSize;

private:
  // private member functions
  std::vector<State> parseLine(std::string line) {
    std::istringstream sline(line);
    int n;
    char c;
    std::vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
  }

  std::vector<std::vector<State>> _map;
  // mutex for reading writing the map
  std::mutex _map_mutex;
};

#endif
