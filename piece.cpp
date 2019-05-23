#include "piece.h"

Piece::Piece()
{
    x = 2;
    y = 2;
    rotation = 0;
    n = 2;
}
void Piece::move_horizontal(int direction)
{
    x += direction;
}
void Piece::move_vertical(int direction)
{
    y += direction;
}
void Piece::rotate()
{
    rotation++;
    if(rotation == 4){
        rotation = 0;
    }
}
