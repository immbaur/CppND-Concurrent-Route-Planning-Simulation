#include <thread>

#include "turtle.h"
#include "astar.h"


std::mutex Turtle::_logic_mutex;

Turtle::Turtle(std::shared_ptr<Map> m, Color c, int i){
  _mapHandle = m;
  _id = i;
  _color = c;
  _currentPos = _mapHandle->getRandPos(true);
  std::cout << "Turtle ID " << _id << ": Muk muk!" << std::endl;
}

Position Turtle::getCurrentPosition(){
  std::lock_guard<std::mutex> lck(_pos_mutex);
  return _currentPos;
};

Position Turtle::getDestination(){
   std::lock_guard<std::mutex> lck(_dest_mutex);
  return _destination;
};

std::vector<Position> Turtle::getPath(){
  std::lock_guard<std::mutex> lck(_path_mutex);
  return _pathToDest;
}

void Turtle::simulate(){
  while(true){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << getId() << " -- setNewDestintion" << '\n';
    setNewDestintion();
    std::cout << getId() << " -- planPathToDestination" << '\n';
    planPathToDestination();
    std::cout << getId() << " -- run" << '\n';
    run();
  }
}

void Turtle::setNewDestintion(){
  std::lock_guard<std::mutex> lck(_dest_mutex);
  _destination = _mapHandle->getRandPos(false);
}

void Turtle::planPathToDestination(){

  int init[2] = {(int)_currentPos.y,(int)_currentPos.x};
  int goal[2] = {(int)_destination.y,(int)_destination.x};
  std::cout << getId() << " -- init: " << init[0] << " " << init[1] << std::endl;
  std::cout << getId() << " -- goal: " << goal[0] << " " << goal[1] << std::endl;

  std::vector<std::vector<Position>> pathWithParent;
  AStar astar;
  bool result = false;
  std::unique_lock<std::mutex> logic_lck(_logic_mutex);
  while (result != true) {
    result = astar.Search(_mapHandle->getMap(), pathWithParent, init, goal);
    if (!result){
      logic_lck.unlock();
      // std::cout << "Try A*Search again" << '\n';
      pathWithParent.clear();
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      logic_lck.lock();
    }
  }
  // std::cout << "pathWithParent Size:" << pathWithParent.size() << std::endl;
  // std::for_each(pathWithParent.begin(), pathWithParent.end(), [](std::vector<Position> &fieldWithParent) {
  //   // /std::cout << "Size:" << fieldWithParent.size() << std::endl;
  //   std::cout << "Pos:" << fieldWithParent.at(0).x;
  //   std::cout << " " << fieldWithParent[0].y << std::endl;
  //   std::cout << "Parent Pos:" << fieldWithParent[1].x;
  //   std::cout << " " << fieldWithParent[1].y << std::endl;
  // });

  auto next = pathWithParent.back();
  Position pos = next.at(0);
  Position parent = next.at(1);
  pathWithParent.pop_back();

  std::lock_guard<std::mutex> lck(_path_mutex);
  _pathToDest.clear();
  _pathToDest.insert(_pathToDest.begin(), pos);

  while (parent != pos) {
    pos = parent;
    _pathToDest.insert(_pathToDest.begin(), pos);
    // find new parent
    for (int i = 0; i < pathWithParent.size(); i++) {
      if (pathWithParent.at(i).at(0) == parent){
        parent = pathWithParent.at(i).at(1);
        pathWithParent.erase(pathWithParent.begin()+i);
        break;
      }
    }
  }
  _mapHandle->reservePathInMap(_pathToDest);

  // std::for_each(_pathToDest.begin(), _pathToDest.end(), [](Position &pos) {
  //   // /std::cout << "Size:" << fieldWithParent.size() << std::endl;
  //   std::cout << "Path Pos:" << pos.x;
  //   std::cout << " " << pos.y << std::endl;
  // });
}

void Turtle::run(){
  std::unique_lock<std::mutex> lck(_path_mutex);
  // remove first field, as this is the field where the turtl is located
  _pathToDest.erase(_pathToDest.begin());

  while (!_pathToDest.empty())
  {
    Position nextField = _pathToDest.front();
    lck.unlock();

    Position current = _currentPos;
    goTo(nextField);
    _mapHandle->freeField(current);

    lck.lock();
    _pathToDest.erase(_pathToDest.begin());
  }
  lck.unlock();
}

void Turtle::goTo(Position pos){
//  std::cout << "got to " << pos.x << " " << pos.y << '\n';
  double x1, x2, y1, y2, dx, dy, xv, yv, completion;
  completion = 0;

  std::unique_lock<std::mutex> lck(_pos_mutex);
  x1 = _currentPos.x;
  y1 = _currentPos.y;
  lck.unlock();

  x2 = pos.x;
  y2 = pos.y;

  dx = x2 - x1;
  dy = y2 - y1;

  while (completion <= 1.0){

    xv = x1 + completion * dx;
    yv = y1 + completion * dy;

    lck.lock();
    _currentPos.x = xv;
    _currentPos.y = yv;
    lck.unlock();

    completion += 0.1;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
  }
}
