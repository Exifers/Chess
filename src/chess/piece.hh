#pragma once

enum color {
  BLACK,
  WHITE
};

class Piece {
  public:
    Piece(char c, enum color color, bool lines, bool diags);
    virtual ~Piece() = 0;

    virtual bool canMoveAt(int x, int y, int nx, int ny);
    virtual bool canEatAt(int x, int y, int nx, int ny);

    char toChar();

    bool lines_get() { return lines_; }
    bool diags_get() { return diags_; } 

    enum color color_get() { return color_; } 
  protected:
    char c_; /* For printing */
    enum color color_;
    /* Motion behavior : */
    bool lines_;
    bool diags_;
};

class Rook : public Piece {
  public:
    Rook(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
};

class Knight : public Piece {
  public:
    Knight(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
};

class Queen : public Piece {
  public:
    Queen(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
};

class King : public Piece {
  public:
    King(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
};

class Bishop : public Piece {
  public:
    Bishop(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
};

class Pawn : public Piece {
  public:
    Pawn(enum color color);
    bool canMoveAt(int x, int y, int nx, int ny) override;
    bool canEatAt(int x, int y, int nx, int ny) override;
};
