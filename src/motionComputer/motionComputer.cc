#include <typeinfo>
#include <iostream>

#include "motionComputer.hh"

MotionComputer::MotionComputer(Chess *chess)
  : chess_(chess)
{}

bool
MotionComputer::isDoable(struct move motion) {
  if (!checkBounds(motion)) {
    std::cerr << "Motion out of bounds : ";
    return false;
  }
  auto piece = chess_->board_get()[motion.posX][motion.posY];
  if (piece == nullptr) /* No piece at this place ! */ {
    std::cerr << "There's no piece in here : ";
    return false;
  }

  try {
    Knight *knight = dynamic_cast<Knight*>(piece);
    if (knight) {
      return isDoableKnight(piece, motion);
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
      std::cerr << "A piece is blocking : ";
      return false;
    }
  }
  auto endPiece = chess_->board_get()[testPosX_][testPosY_];
  if (endPiece != nullptr) {
    if (endPiece->color_get() == piece->color_get()) {
      std::cerr << "Cannot eat piece of the same color : ";
      return false;
    }
  }
  
  /* Eating or maybe not */
  return true;
}

bool
MotionComputer::checkMotion(Piece *piece, struct move motion) {
  if (!checkBounds(motion)) {
    std::cerr << "Motion out of bounds : ";
    return false;
  }
  if (!checkNotPass(motion)) {
    std::cerr << "You cannot pass your turn : ";
    return false;
  }
  if (!checkPieceDirection(piece, motion)) {
    std::cerr << "Piece cannot go that way : ";
    return false;
  }
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
MotionComputer::isDoableKnight(Piece* piece, struct move motion) {
  
  auto endPiece = chess_->board_get()[motion.newPosX][motion.newPosY];
  if (endPiece != nullptr) {
    if (endPiece->color_get() == piece->color_get())
      return false;
  }

  int dx = abs(motion.newPosX - motion.posX);
  int dy = abs(motion.newPosY - motion.posY);
  if (dx == 1 && dy == 2) {
    return true;
  }
  if (dx == 2 && dy == 1) {
    return true;
  }
  return false;
}

bool
MotionComputer::isDoablePawn(Piece *piece, struct move motion) {
  int dx = motion.newPosX - motion.posX;
  int dy = motion.newPosY - motion.posY;
  if (abs(dx) != 1 && abs(dx) != 0) {
    std::cerr << "Pawn can move only one unit horizontally : ";
    return false;
  }
  if (abs(dy) != 1 && abs(dy) != 0) {
    std::cerr << "Pawn can move only one unit vertically : ";
    return false;
  }

  /* Checking if it goes in the right direction : */
  if (piece->color_get() == Piece::BLACK && dx != 1) { 
    std::cerr << "Pawn cannot go backward : ";
    return false;
  }
  if (piece->color_get() == Piece::WHITE && dx != -1) {
    std::cerr << "Pawn cannot go backward : ";
    return false;
  }

  if (abs(dy) == 1) /* Supposed to eat */ {
    auto endPiece = chess_->board_get()[motion.newPosX][motion.newPosY];
    if (endPiece == nullptr) {
      std::cerr << "Pawn cannot go along a diagonal without eating : ";
      return false;
    }
    if (endPiece->color_get() == piece->color_get()) {
      std::cerr << "You cannot eat your own piece ! : ";
      return false;
    }
  }
  return true;
}
