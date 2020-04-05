#include "graphic.h"

Graphic::Graphic(std::shared_ptr<Map> m){
  _mapHandle = m;
  _multiplier = 70;
  setupWorld();
}

void Graphic::updateGraphic(std::vector<std::shared_ptr<Turtle>> turtles){
  cv::Mat dynamicMap = _staticMap.clone();

  std::for_each(turtles.begin(), turtles.end(), [&dynamicMap, this](std::shared_ptr<Turtle> &turtlePtr){
    drawTurtlePosition(dynamicMap, turtlePtr);
    drawTurtleDestination(dynamicMap, turtlePtr);
    drawTurtlePath(dynamicMap, turtlePtr);
  });
  cv::imshow(_windowName, dynamicMap);
  cv::waitKey(33);
}

void Graphic::setupWorld(){
  // creat opencv window
  _windowName = "Turtle world";
  cv::namedWindow( _windowName, cv::WINDOW_AUTOSIZE );

  // creat a static map that contains the obstacles only
  _staticMap = cv::Mat(_mapHandle->rowSize()*_multiplier, _mapHandle->colSize()*_multiplier, CV_8UC3, cv::Scalar(0,0,0));
  // iterate throu all map fields
  for (int y=0; y<_mapHandle->rowSize(); y++){
    for (int x=0; x<_mapHandle->colSize(); x++){
      // check if obstacle exist on field
      if (_mapHandle->getMap()[y][x] == State::kObstacle)
        // instert obstacle in the world
        drawObstacle(x,y);
    }
  }
}

void Graphic::drawObstacle(double x, double y){
  double _x = x*_multiplier+_multiplier/2;
  double _y = y*_multiplier+_multiplier/2;
  double _r = _multiplier/2;
  cv::circle(_staticMap, cv::Point(_x,_y), _r, cv::Scalar(255,255,255), -1, 8, 0);
}

void Graphic::drawTurtlePosition(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr){
  Position pos = turtlePtr->getCurrentPosition();
  Color color = turtlePtr->getColor();

  double _x = pos.x*_multiplier+_multiplier/2;
  double _y = pos.y*_multiplier+_multiplier/2;
  double _r = _multiplier/2;
  cv::circle(dynamicMap, cv::Point(_x, _y), _r, cv::Scalar(color.r,color.g,color.b),-1, 8,0);
}

void Graphic::drawTurtleDestination(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr){
  Position dest = turtlePtr->getDestination();
  Color color = turtlePtr->getColor();

  double _x = dest.x*_multiplier+_multiplier/2;
  double _y = dest.y*_multiplier+_multiplier/2;
  double _r = _multiplier/2;
  cv::circle(dynamicMap, cv::Point(_x, _y), _r, cv::Scalar(color.r,color.g,color.b),2, 8,0);
}

void Graphic::drawTurtlePath(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr){
  Position pos = turtlePtr->getCurrentPosition();
  Color color = turtlePtr->getColor();

  std::vector<Position> path = turtlePtr->getPath();
  // draw first step of the path
  if (path.size() >= 1){
    line(dynamicMap, cv::Point(pos.x*_multiplier+_multiplier/2,pos.y*_multiplier+_multiplier/2), cv::Point(path.begin()->x*_multiplier+_multiplier/2,path.begin()->y*_multiplier+_multiplier/2), cv::Scalar(color.r,color.g,color.b), 5, 8, 0);
  }
  // draw rest of the path
  if (path.size() >= 2){
    for (auto iterator = path.begin(); iterator < path.end()-1; ++iterator) {
      auto next = std::next(iterator, 1); // get a pointer to the next element
      line(dynamicMap, cv::Point(iterator->x*_multiplier+_multiplier/2,iterator->y*_multiplier+_multiplier/2), cv::Point(next->x*_multiplier+_multiplier/2,next->y*_multiplier+_multiplier/2), cv::Scalar(color.r,color.g,color.b), 5, 8, 0);
    }
  }
}
