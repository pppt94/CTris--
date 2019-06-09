#include "piece.h"

Piece::Piece()
{
    qsrand(time(NULL));

    x = 2;
    y = -3;
    rotation = 0;
    n = qrand() % 7;
    next_n = qrand() % 7;

}
void Piece::move_horizontal(int direction)
{
    x += direction;
}
void Piece::move_vertical(int direction)
{
    y += direction;
}
void Piece::rotate(int direction)
{
    rotation += direction;
    if(rotation == 4){
        rotation = 0;
    }
    if(rotation == -1){
        rotation = 4;
    }
}
void Piece::resetPiece()
{
    x = 2;
    y = -4;
    rotation = 0;
    n = next_n;
    next_n = qrand() % 7;;
}
