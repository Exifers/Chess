#include <chess/chess.hh>
#include <chess/piece.hh>

class MotionComputer {
  public:
    MotionComputer(Chess *chess)
      : chess_(chess)
    {}
    bool isDoable(Piece *piece, struct Chess::move motion);
  private:
    Chess *chess_;
    int testPosX_;
    int testPosY_;

    /* Increments the test position based on the piece motion behavior */
    /* (Not used for knights) */
    void incTestPos(Piece *piece);

    /* Special piece behaviors : */
    bool isDoableKnight(struct Chess::move);
    bool isDoablePawn(Piece *piece, struct Chess::move);
    // TODO rock
    // TODO check if King is threatened

    bool isDoableGeneric(Piece *piece, struct Chess::move);
};
