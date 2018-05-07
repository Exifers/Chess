#include <iostream>

#include "chess.hh"

Chess::Chess()
  : board_(nullptr), motionComputer_(MotionComputer(this))
{
  board_ = new Piece**[8];
  for (int i = 0; i < 8; i++) {
    board_[i] = new Piece*[8];
    for (int j = 0; j < 8; j++) {
      if (i == 1) { // black pawns
        board_[i][j] = new Pawn(BLACK);
      }
      else if (i == 6) { // white pawns
        board_[i][j] = new Pawn(WHITE); 
      }
      else {
        board_[i][j] = nullptr;
      }
    }
  }
  board_[0][0] = new Rook(BLACK);
  board_[0][1] = new Knight(BLACK);
  board_[0][2] = new Bishop(BLACK);
  board_[0][3] = new King(BLACK);
  board_[0][4] = new Queen(BLACK);
  board_[0][5] = new Bishop(BLACK);
  board_[0][6] = new Knight(BLACK);
  board_[0][7] = new Rook(BLACK);
  board_[7][0] = new Rook(WHITE);
  board_[7][1] = new Knight(WHITE);
  board_[7][2] = new Bishop(WHITE);
  board_[7][3] = new King(WHITE);
  board_[7][4] = new Queen(WHITE);
  board_[7][5] = new Bishop(WHITE);
  board_[7][6] = new Knight(WHITE);
  board_[7][7] = new Rook(WHITE);
}

Chess::~Chess() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      delete board_[i][j];
    }
    delete board_[i];
  }
  delete board_;
}

bool
Chess::end() {
  return false;
}

bool
Chess::isDoable(struct move move) {
  return motionComputer_.isDoable(move); 
}

void
Chess::apply(struct move move) {
  auto& endPiece = board_[move.newPosX][move.newPosY];
  if (endPiece != nullptr)
    delete endPiece;
  endPiece = board_[move.posX][move.posY];
  board_[move.posX][move.posY] = nullptr;
}

void
Chess::print() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board_[i][j] != nullptr)
        std::cout << board_[i][j]->toChar();
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}
