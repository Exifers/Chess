#pragma once

#include <chess/chess.hh>

class PlayRoutine {
  public:
    PlayRoutine(Chess& chess);
    static void showTitle();
    void run();
  private:
    Chess chess_;
    void end(int player);
    struct Chess::move askMove();
    void playP1();
    void playP2();
    struct Chess::move getMove(); 
};
