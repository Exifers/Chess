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
    struct move askMove();
    void playP1();
    void playP2();
    struct move getMove(); 
};
