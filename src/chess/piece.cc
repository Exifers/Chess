#include <cstdlib>

#include "piece.hh"

/*---------
  | Piece |
  ---------*/

Piece::Piece(char c, std::string name, enum color color, bool lines, bool diags)
  : c_(c), name_(name), color_(color), lines_(lines), diags_(diags)
{}

Piece::~Piece()
{}

char
Piece::toChar() {
  return c_;
}

bool
Piece::canMoveAt(int x, int y, int nx, int ny) {
  /* One can't pass his turn at chess !*/
  return (x != nx) && (y != ny);
}

bool
Piece::canEatAt(int x, int y, int nx, int ny) {
  return canMoveAt(x, y, nx, ny);
}

/*--------
  | Rook |
  --------*/

Rook::Rook(enum color color)
  : Piece('r', "rock", color, true, false)
{}

bool
Rook::canMoveAt(int x, int y, int nx, int ny) {
  if (x == nx || y == ny)
    return true && Piece::canMoveAt(x, y, nx, ny);
  return false;
}

/*----------
  | Knight |
  ----------*/

Knight::Knight(enum color color)
  : Piece('k', "knight", color, false, false)
{}


bool
Knight::canMoveAt(int x, int y, int nx, int ny) {
  /* LOL */
  int dx = abs(nx - x);
  int dy = abs(ny - y);
  if (dx == 1 && dy == 2) {
    return true;
  }
  if (dx == 2 && dy == 1) {
    return true;
  }
  return false;
}

/*---------
  | Queen |
  ---------*/

Queen::Queen(enum color color)
  : Piece('q', "queen", color, true, true)
{}

bool
Queen::canMoveAt(int x, int y, int nx, int ny) {
  if (x == nx || y == ny) {
    return true && Piece::canMoveAt(x, y, nx, ny);
  }
  int dx = abs(nx - x);
  int dy = abs(ny - y);
  if (dx == dy)
    return true && Piece::canMoveAt(x, y, nx, ny);
  return false; 
}

/*--------
  | King |
  --------*/

King::King(enum color color)
  : Piece('K', "king", color, true, true)
{}

bool
King::canMoveAt(int x, int y, int nx, int ny) {
  int dx = abs(nx - x);
  int dy = abs(ny - y);
  if (dx <= 1 && dy <= 1)
    return true && Piece::canMoveAt(x, y, nx, ny);
  return false;
}

/*----------
  | Bishop |
  ----------*/

Bishop::Bishop(enum color color)
  : Piece('b', "bishop", color, false, true)
{}

bool
Bishop::canMoveAt(int x, int y, int nx, int ny) {
  int dx = abs(nx - x);
  int dy = abs(ny - y);
  if (dx == dy)
    return true && Piece::canMoveAt(x, y, nx, ny);
  return false;
}

/*--------
  | Pawn |
  --------*/

Pawn::Pawn(enum color color)
  : Piece('p', "pawn", color, true, false)
{}

bool
Pawn::canMoveAt(int x, int y, int nx, int ny) { 
  int dx = abs(nx - x);
  int dy = ny - y;
  if (dx != 0)
    return false;
  switch(color_) {
    case WHITE:
      return dy == -1;
    case BLACK:
      return dy == 1;
    default:
      return false;
  }
}

bool
Pawn::canEatAt(int x, int y, int nx, int ny) {
  int dx = abs(nx - x);
  int dy = ny - y;
  if (dx != 1)
    return false;
  switch(color_) {
    case WHITE:
      return dy == -1;
    case BLACK:
      return dy == 1;
    default:
      return false;
  }
}
