#include <playRoutine/playRoutine.hh>
#include <chess/chess.hh>
#include <ui/ui.hh>

int main(int argc, char **argv) {
  Chess chess = Chess();
  UI ui = UI(chess);
  return ui.launch(argc, argv);
}
