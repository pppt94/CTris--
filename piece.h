#ifndef PIECE_H
#define PIECE_H

#include <QMainWindow>
#include <stdlib.h>
#include <time.h>



class Piece
{
public:
    Piece();
    void move_horizontal(int direction);
    void move_vertical(int direction);
    void rotate();

    int x, y, rotation;
    int n;

};

#endif // PIECE_H
