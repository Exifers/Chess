#pragma once

class Chess;
class MotionComputer;

#include <experimental/optional>

#include <motionComputer/motionComputer.hh>

#include "piece.hh"

struct move {
  int posX;
  int posY;
  int newPosX;
  int newPosY;
  enum color player;
};

class Chess {
  public:
    Chess();
    ~Chess();

    bool end(); 
    bool isDoable(struct move move);
    void apply(struct move move);
    void print();

    Piece ***board_get() { return board_; } 

  private:
    Piece  ***board_;
    MotionComputer motionComputer_;
};
