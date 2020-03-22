#include <thread>

#include "turtle.h"


Turtle::Turtle(){
  std::cout << "Muk muk!" << std::endl;
}

void Turtle::sim(){
  while(true){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    getNewDestintion();
    planPathToDestination();
    run();
  }
}

void Turtle::setColor(Color col){
  color = col;
}


double Turtle::getX() {return _current.x;}
double Turtle::getY() {return _current.y;}

void Turtle::setX( double X) {_current.x = X;}
void Turtle::setY( double Y) {_current.y = Y;}

void Turtle::getNewDestintion(){
  _destination.x = rand() % 10;
  _destination.y = rand() % 10;
}

void Turtle::planPathToDestination(){

  _pathToDest.clear();

  //_pathToDest.push_back(_current);

  for(int i=0; i<3; i++){
    Position p = {rand() % 10,rand() % 10};
    _pathToDest.push_back(p);
  }
  _pathToDest.push_back(_destination);

}

void Turtle::run(){
  while (!_pathToDest.empty())
  {
     goTo(_pathToDest.front());
     _pathToDest.erase(_pathToDest.begin());
  }
}

const std::vector<Position> Turtle::getPath() const{
  std::vector<Position> v = _pathToDest;
  return v;
}


void Turtle::goTo(Position pos){

  double x1, x2, y1, y2, dx, dy, xv, yv, completion;
  completion = 0;

  x1 = _current.x;
  y1 = _current.y;

  x2 = pos.x;
  y2 = pos.y;

  dx = x2 - x1;
  dy = y2 - y1;

  while (completion <= 1.0){

    xv = x1 + completion * dx;
    yv = y1 + completion * dy;

    _current.x = xv;
    _current.y = yv;

    completion += 0.1;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
