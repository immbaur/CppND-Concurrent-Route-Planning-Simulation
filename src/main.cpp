#include <iostream>
#include <chrono>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "turtle.h"

int main() {
  //
  int map [11][10] =
  {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,1,1,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
  };

    std::cout << "Start application" << std::endl;
    //std::shared_ptr<MapHandle> mapHandle;

    int rowSize = sizeof(map) / sizeof(map[0]);
    int columnSize = sizeof(map[0])/sizeof(map[0][0]);

    std::cout << "rowSize" << rowSize<< std::endl;
    std::cout << "columnSize" << columnSize<< std::endl;


    int multiplier = 70;
    cv::Mat mat(rowSize*multiplier, columnSize*multiplier, CV_8UC3, cv::Scalar(0,0,0));

    for (int i=0; i<rowSize; i++){
      for (int j=0; j<columnSize; j++){
        if ( map[i][j] )
          cv::circle(mat, cv::Point(j*multiplier+multiplier/2,i*multiplier+multiplier/2),multiplier/2, cv::Scalar(255,255,255),-1, 8,0);
      }
    }

    std::vector<std::shared_ptr<Turtle>> turtleVec;

    int nTurtles = 2;

    // build turtles and store them in vector
    for (int nt=0; nt<nTurtles; nt++){
      turtleVec.push_back(std::make_shared<Turtle>());
      turtleVec.at(nt)->setColor({rand()%255,rand()%255,rand()%255});
    }

    // start thread for each turtle
    std::vector<std::thread> v;
    std::for_each(turtleVec.begin(), turtleVec.end(), [&v](std::shared_ptr<Turtle> &t) {
       v.emplace_back(std::thread(&Turtle::sim, t));
    });

    // create new window
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
    while(true){
      // remove turtle and path objects objects from map
      cv::Mat turtleMat = mat.clone();

      // draw turtle positions an paths into the map
      std::for_each(turtleVec.begin(), turtleVec.end(), [&turtleMat,multiplier](std::shared_ptr<Turtle> &turtlePtr){
        cv::circle(turtleMat, cv::Point(turtlePtr->getX()*multiplier+multiplier/2,turtlePtr->getY()*multiplier+multiplier/2),multiplier/2, cv::Scalar(turtlePtr->color.r,turtlePtr->color.g,turtlePtr->color.b),-1, 8,0);

        std::vector<Position> path = turtlePtr->getPath();
        // draw first step of the path
        if (path.size() >= 1){
          line(turtleMat, cv::Point(turtlePtr->getX()*multiplier+multiplier/2,turtlePtr->getY()*multiplier+multiplier/2), cv::Point(path.begin()->x*multiplier+multiplier/2,path.begin()->y*multiplier+multiplier/2), cv::Scalar(turtlePtr->color.r,turtlePtr->color.g,turtlePtr->color.b), 5, 8, 0);
        }
        // draw rest of the path
        if (path.size() >= 2){
          for (auto iterator = path.begin(); iterator < path.end()-1; ++iterator) {
            auto next = std::next(iterator, 1); // get a pointer to the next element
            line(turtleMat, cv::Point(iterator->x*multiplier+multiplier/2,iterator->y*multiplier+multiplier/2), cv::Point(next->x*multiplier+multiplier/2,next->y*multiplier+multiplier/2), cv::Scalar(turtlePtr->color.r,turtlePtr->color.g,turtlePtr->color.b), 5, 8, 0);
          }
        }
      });

      cv::imshow("test", turtleMat);
      cv::waitKey(33);

    }
    return 0;
}
