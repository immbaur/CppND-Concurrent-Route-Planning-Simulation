#include <iostream>
#include <chrono>
#include <vector>

#include "mystructs.h"

class Turtle {

public:
  Turtle();
  void sim();
  void setColor(Color col);

  double getX();
  double getY();

  const std::vector<Position> getPath() const;

  Color color = {0,0,0};

private:
  // member functions
  void setX( double X);
  void setY( double Y);

  // public memeber functions
  void getNewDestintion();
//  void setDestination();
  void planPathToDestination();
  void run();

  void goTo(Position pos);

  // member variables
  Position _start = {0,0};
  Position _current = {0,0};
  Position _destination = {0,0};

  // std::shared_ptr<MapHandle> _mapHandle;
  std::vector<Position> _pathToDest;
};
