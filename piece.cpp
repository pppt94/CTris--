#include "piece.h"

Piece::Piece()
{
    x = 2;
    y = 2;
    rotation = 0;
    n = 0;
}
void Piece::move_horizontal(int direction)
{
    x += direction;
}
