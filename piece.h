#ifndef PIECE_H
#define PIECE_H

#include <QMainWindow>

class Piece
{
public:
    Piece();
    void move_horizontal(int direction);
    void move_vertical(int direction);
    void rotate();
    void resetPiece();

    int x, y, rotation;
    int n;


};

#endif // PIECE_H
