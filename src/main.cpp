#include <iostream>
#include <chrono>
#include <thread>


#include "turtle.h"
#include "graphic.h"


int main() {
    // set number of turtles
    int nTurtles = 4;

    std::cout << "Start application" << std::endl;

    // create map handle which is a pointer to the map object
    std::shared_ptr<Map> mapHandle = std::make_shared<Map>("../map.txt");
    // create graphic object and pass in the map
    Graphic world = Graphic(mapHandle);

    // setup turtle vector
    std::vector<std::shared_ptr<Turtle>> turtleVec;
    // build turtles and store them in the vector
    for (int id=0; id<nTurtles; id++){
      turtleVec.push_back(std::make_shared<Turtle>(mapHandle, Color{rand()%255,rand()%255,rand()%255}, id));
    }

    // start simulation thread for each turtle
    std::vector<std::thread> v;
    std::for_each(turtleVec.begin(), turtleVec.end(), [&v](std::shared_ptr<Turtle> &t) {
       v.emplace_back(std::thread(&Turtle::simulate, t));
    });

    while(true){
      // 30Hz graphic update
      world.updateGraphic(turtleVec);
    }

    return 0;
}
