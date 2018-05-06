#pragma once

#include <experimental/optional>

#include "piece.hh"

class Chess {
  public:
    Chess();
    ~Chess();

    struct move {
      int posX;
      int posY;
      int newPosX;
      int newPosY;
    };

    bool end(); 
    bool isDoable(struct move move);
    void apply(struct move move);
    void print();

  private:
    Piece  ***board_;
};
