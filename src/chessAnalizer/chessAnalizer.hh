#pragma once

#include <chess/chess.hh>

struct colorWrapper {
  enum color color;
  enum color it() { return color; }
  enum color other() {
    return color == BLACK ? WHITE : BLACK;
  }
};

class ChessAnalizer {
  public:
    ChessAnalizer(Chess *chess)
      : chess_(chess)
    {}

    /* To escape a check, a player can either move the king or move a piece */

    bool endWhite() { return false; }
    bool endBlack() { return false; }

  private:
    Chess *chess_;

    bool endColor(struct colorWrapper color);
};
