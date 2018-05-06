#include <typeinfo>
#include <iostream>

#include "motionComputer.hh"

MotionComputer::MotionComputer(Chess *chess)
  : chess_(chess)
{}

bool
MotionComputer::isDoable(struct move motion) {
  if (!checkBounds(motion))
    return false;
  auto piece = chess_->board_get()[motion.posX][motion.posY];
  if (piece == nullptr) /* No piece at this place ! */
    return false;

  std::cout << "bounds and piece ok" << std::endl;

  try {
    Knight *knight = dynamic_cast<Knight*>(piece);
    if (knight) {
      return isDoableKnight(motion);
    }
    Pawn *pawn = dynamic_cast<Pawn*>(piece);
    if (pawn) {
      return isDoablePawn(piece, motion);
    }
  }
  catch (const std::bad_cast& e)
  {} 
  return isDoableGeneric(piece, motion);
}

void
MotionComputer::incTestPos(struct move motion) {
  int posX = motion.posX;
  int posY = motion.posY;
  int newPosX = motion.newPosX;
  int newPosY = motion.newPosY;
  int dx = newPosX - posX;
  int dy = newPosY - posY;
  int signX = dx > 0 ? 1 : dx < 0 ? -1 : 0; 
  int signY = dy > 0 ? 1 : dy < 0 ? -1 : 0;

  testPosX_ += signX;
  testPosY_ += signY; 
}

bool
MotionComputer::isDoableGeneric(Piece *piece, struct move motion) {

  /* Checks independant from the other pieces on the board */
  if (!checkMotion(piece, motion))
    return false;

  testPosX_ = motion.posX;
  testPosY_ = motion.posY;  
  incTestPos(motion); 
  while (testPosX_ != motion.newPosX
      || testPosY_ != motion.newPosY) {
    incTestPos(motion); 
    if (chess_->board_get()[testPosX_][testPosY_] != nullptr) {
      /* A piece is blocking the view */
      return false;
    }
  }
  auto endPiece = chess_->board_get()[testPosX_][testPosY_];
  if (endPiece != nullptr) {
    if (endPiece->color_get() == piece->color_get()) {
      /* Cannot eat a piece of the same color */
      return false;
    }
  }
  
  /* Eating or maybe not */
  return true;
}

bool
MotionComputer::checkMotion(Piece *piece, struct move motion) {
  if (!checkBounds(motion))
    return false;
  if (!checkNotPass(motion))
    return false;
  if (!checkPieceDirection(piece, motion))
    return false;
  return true;
}

bool
MotionComputer::checkPieceDirection(Piece *piece, struct move motion) {
  if (piece->lines_get()) {
    if (motion.posX == motion.newPosX)
      return true;
    if (motion.posY == motion.newPosY)
      return true;
  }
  if (piece->diags_get()) {
    int dx = abs(motion.newPosX - motion.posX);
    int dy = abs(motion.newPosY - motion.posY);
    if (dx == dy)
      return true;
  }
  return false;
}

bool
MotionComputer::checkBounds(struct move motion) {
  if (motion.posX < 0 || motion.posX >= 8)
    return false;
  if (motion.posY < 0 || motion.posY >= 8)
    return false;
  if (motion.newPosX < 0 || motion.newPosX >= 8)
    return false;
  if (motion.newPosY < 0 || motion.newPosY >= 8)
    return false;
  return true;
}

bool
MotionComputer::checkNotPass(struct move motion) {
  return motion.posX != motion.newPosX || motion.posY != motion.newPosY;
}

bool
MotionComputer::isDoableKnight(struct move motion) {
  motion = motion;
  return true;
}

bool
MotionComputer::isDoablePawn(Piece *piece, struct move motion) {
  piece = piece;
  motion = motion;
  return true;
}
