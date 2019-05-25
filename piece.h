#ifndef PIECE_H
#define PIECE_H

#include <QMainWindow>

class Piece
{
public:
    Piece();
    void move_horizontal(int direction);
    void move_vertical(int direction);
    void rotate(int direction);
    void resetPiece();

    int x, y, rotation;
    int n;
    int next_n;


};

#endif // PIECE_H
