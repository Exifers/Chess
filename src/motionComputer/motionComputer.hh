#pragma once

class Chess;
class MotionComputer;

#include <chess/piece.hh>

class MotionComputer {
  public:
    MotionComputer(Chess *chess);
    bool isDoable(struct move motion);
  private:
    Chess *chess_;
    int testPosX_;
    int testPosY_;

    /* Increments the test position based on the piece motion behavior */
    /* (Not used for special motion behaviors) */
    void incTestPos(struct move motion);

    /* Special piece behaviors : */
    bool isDoableKnight(Piece *piece, struct move motion);
    bool isDoablePawn(Piece *piece, struct move motion);
    // TODO rock
    // TODO check if King is threatened

    bool isDoableGeneric(Piece *piece, struct move motion);

    /* Checks weather the motion is valid according to :
    ** - Piece::diags and Piece::lines
    ** - it is not equivalent to pass
    */
    bool checkMotion(Piece *piece, struct move motion);

    bool checkPieceDirection(Piece *piece, struct move motion);
    bool checkBounds(struct move motion);
    bool checkNotPass(struct move motion);
};

#include <chess/chess.hh>
