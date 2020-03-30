#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

struct Position {
  double x;
  double y;

  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Position& other) const {
    return x != other.x || y != other.y;
  }
};

struct Color {
  double r;
  double g;
  double b;
};


#endif
