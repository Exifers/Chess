#pragma once

class Piece {
  public:
    enum color {
      BLACK,
      WHITE
    };

    Piece(char c, enum color color);
    virtual ~Piece() = 0;

    virtual bool canMoveAt(int x, int y, int nx, int ny);
    virtual bool canEatAt(int x, int y, int nx, int ny);

    char toChar();
    
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
