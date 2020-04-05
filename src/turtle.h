#ifndef TRUTLE_H
#define TRUTLE_H

#include <iostream>
#include <chrono>
#include <vector>
#include <mutex>

#include "mystructs.h"
#include "map.h"

class Turtle {

public:
  // constructor
  Turtle(std::shared_ptr<Map> m, Color c, int i);
  // public member functions
  int getId(){return _id;};
  Color getColor(){return _color;};

  Position getCurrentPosition();

  Position getDestination();

  std::vector<Position> getPath();
  // start simulation of the turtle
  void simulate();

private:
  // private memeber functions
  void setNewDestintion();
  void planPathToDestination();
  void run();
  void goTo(Position pos);

  // private member variables
  int _id;
  Color _color;
  Position _currentPos;
  Position _destination;

  std::shared_ptr<Map> _mapHandle;
  // this is the queue for storing all field positions of the path
  std::vector<Position> _pathToDest;

  // mutexes for save reading and writing
  std::mutex _pos_mutex;
  std::mutex _dest_mutex;
  std::mutex _path_mutex;
  // global turtle mutex to make sure that the turtles are planning the path after each other
  static std::mutex _logic_mutex;
};

#endif
