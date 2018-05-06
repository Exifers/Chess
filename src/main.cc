#include <playRoutine/playRoutine.hh>
#include <chess/chess.hh>

int main(void) {
  PlayRoutine::showTitle();
  Chess chess = Chess();
  PlayRoutine playRoutine = PlayRoutine(chess);
  playRoutine.run();
  return 0;
}
