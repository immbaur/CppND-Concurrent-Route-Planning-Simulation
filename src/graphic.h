#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "map.h"
#include "turtle.h"

class Graphic {

public:
  Graphic(std::shared_ptr<Map> m);

  void updateGraphic(std::vector<std::shared_ptr<Turtle>> turtles);

private:
  void setupWorld();

  void drawObstacle(double x, double y);

  void drawTurtlePosition(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr);

  void drawTurtleDestination(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr);

  void drawTurtlePath(cv::Mat &dynamicMap, std::shared_ptr<Turtle> &turtlePtr);

  double _multiplier;
  cv::Mat _staticMap;
  std::string _windowName;
  std::shared_ptr<Map> _mapHandle;

};
