#include <iostream>

#include "chess.hh"

Chess::Chess() {
  board_ = new Piece**[8];
  for (int i = 0; i < 8; i++) {
    board_[i] = new Piece*[8];
    for (int j = 0; j < 8; j++) {
      if (i == 1) { // black pawns
        board_[i][j] = new Pawn(Piece::BLACK);
      }
      else if (i == 6) { // white pawns
        board_[i][j] = new Pawn(Piece::WHITE); 
      }
      else {
        board_[i][j] = nullptr;
      }
    }
  }
  board_[0][0] = new Rook(Piece::BLACK);
  board_[0][1] = new Knight(Piece::BLACK);
  board_[0][2] = new Bishop(Piece::BLACK);
  board_[0][3] = new King(Piece::BLACK);
  board_[0][4] = new Queen(Piece::BLACK);
  board_[0][5] = new Bishop(Piece::BLACK);
  board_[0][6] = new Knight(Piece::BLACK);
  board_[0][7] = new Rook(Piece::BLACK);
  board_[7][0] = new Rook(Piece::WHITE);
  board_[7][1] = new Knight(Piece::WHITE);
  board_[7][2] = new Bishop(Piece::WHITE);
  board_[7][3] = new King(Piece::WHITE);
  board_[7][4] = new Queen(Piece::WHITE);
  board_[7][5] = new Bishop(Piece::WHITE);
  board_[7][6] = new Knight(Piece::WHITE);
  board_[7][7] = new Rook(Piece::WHITE);
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
  std::cout << "Testing if doable" << std::endl;
  int posX = move.posX;
  int posY = move.posY;
  if (board_[posX][posY]->toChar() == 'k') /* knight */ {
    std::cout << "Found Knight : passing" << std::endl;
    return true;
  }
  int newPosX = move.newPosX;
  int newPosY = move.newPosY;
  //TODO check bounds
  int dx = newPosX - posX;
  int dy = newPosY - posY;
  int signX = dx > 0 ? 1 : dx < 0 ? -1 : 0; 
  int signY = dy > 0 ? 1 : dy < 0 ? -1 : 0;
  int curX = posX + signX;
  int curY = posY + signY;
  std::cout << "curX : " << curX << ", curY : " << curY << ", signX : " << signX << ", signY : " << signY << std::endl;
  std::cout << "newPosX  : " << newPosX << ", newPosY : " << newPosY << std::endl;
  while (curX != newPosX || curY != newPosY) {
    std::cout << "Testing free slot" << std::endl;
    if (board_[curX][curY] != nullptr)
      return false; // a piece obstructs the view
    curX += signX;
    curY += signY;
  }
  //TODO check if King is threatened
  return true;
}

void
Chess::apply(struct move move) {
  move = move;
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
