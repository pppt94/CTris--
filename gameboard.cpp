#include "gameboard.h"
#include "piece.h"
#include <iostream>

std::string shapes[7][4][5] =
   {{{"..X..",
      "..X..",
      "..X..",
      "..X..",
      "....."},
     {".....",
      "XXXX.",
      ".....",
      ".....",
      "....."},
     {"..X..",
      "..X..",
      "..X..",
      "..X..",
      "....."},
     {".....",
      "XXXX.",
      ".....",
      ".....",
      "....."}},
    {{".....",
      ".....",
      "..XX.",
      "..XX.",
      "....."},
     {".....",
      ".....",
      "..XX.",
      "..XX.",
      "....."},
     {".....",
      ".....",
      "..XX.",
      "..XX.",
      "....."},
     {".....",
      ".....",
      "..XX.",
      "..XX.",
      "....."},},
    {{".....",
      ".....",
      "..XX.",
      ".XX..",
      "....."},
     {".....",
      "..X..",
      "..XX.",
      "...X.",
      "....."},
     {".....",
      ".....",
      "..XX.",
      ".XX..",
      "....."},
     {".....",
      "..X..",
      "..XX.",
      "...X.",
      "....."}},
    {{".....",
      ".....",
      ".XX..",
      "..XX.",
      "....."},
     {".....",
      "..X..",
      ".XX..",
      ".X...",
      "....."},
     {".....",
      ".....",
      ".XX..",
      "..XX.",
      "....."},
     {".....",
      "..X..",
      ".XX..",
      ".X...",
      "....."}},
    {{".....",
      "..X..",
      ".XXX.",
      ".....",
      "....."},
     {".....",
      "..X..",
      "..XX.",
      "..X..",
      "....."},
     {".....",
      ".....",
      ".XXX.",
      "..X..",
      "....."},
     {".....",
      "..X..",
      ".XX..",
      "..X..",
      "....."}},
    {{".....",
      "..X..",
      "..X..",
      ".XX..",
      "....."},
     {".....",
      ".X...",
      ".XXX.",
      ".....",
      "....."},
     {".....",
      "..XX.",
      "..X..",
      "..X..",
      "....."},
     {".....",
      ".....",
      ".XXX.",
      "...X.",
      "....."}},
    {{".....",
      "..X..",
      "..X..",
      "..XX.",
      "....."},
     {".....",
      ".....",
      ".XXX.",
      ".X...",
      "....."},
     {".....",
      ".XX..",
      "..X..",
      "..X..",
      "....."},
     {".....",
      "...X.",
      ".XXX.",
      ".....",
      "....."}}};
QColor piece_col[7] = {Qt::red, Qt::yellow, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::gray};

Gameboard::Gameboard(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    createBoard();
    timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateBoard()));
    timer->start(400);

    gameOver = false;
}



void Gameboard::createBoard(){

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            gameboard[i][j] = QColor(Qt::white);
        }
    }
}

void Gameboard::updateBoard()
{
    curr_piece.move_vertical(1);
    if(checkCollision()){
        curr_piece.move_vertical(-1);
        lockPiece();

        curr_piece.resetPiece();
    }
    clearRows();
    this->repaint();
}

bool Gameboard::checkCollision()
{
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(shapes[curr_piece.n][curr_piece.rotation][i][j] == 'X'){
                if((curr_piece.x + j) < 0 || (curr_piece.x + j) == 10){
                    return true;
                }
                if((curr_piece.y + i) == 20 || (gameboard[curr_piece.y+i][curr_piece.x+j] != QColor(Qt::white) && curr_piece.y+i > 0)){
                    return true;
                }
            }
        }
    }
    return false;
}

void Gameboard::lockPiece()
{
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(shapes[curr_piece.n][curr_piece.rotation][i][j] == 'X'){
                gameboard[curr_piece.y+i][curr_piece.x+j] = piece_col[curr_piece.n];
            }
        }
    }
}

void Gameboard::clearRows()
{
    bool ifFull = true;
    int rowsCount = 0;
    int start = 0;

    for(int i = 19; i >= 0; i--){
        ifFull = true;
        for(int j = 0; j < 10; j++){
            if(gameboard[i][j] == QColor(Qt::white)){
                ifFull = false;
            }
        }
        if(ifFull){
            start = start < i ? i : start;
            rowsCount++;
        }

    }

    for(int i = start; i >= 0; i--){
        for(int j = 0; j < 10; j++){
            if(i-rowsCount < 0){
                gameboard[i][j] = QColor(Qt::white);
            }
            else {
                gameboard[i][j] = gameboard[i-rowsCount][j];
            }
        }
    }

}

void Gameboard::instantDrop()
{
    while(!checkCollision()){
        curr_piece.move_vertical(1);
    }
    curr_piece.move_vertical(-1);

    this->repaint();
}
void Gameboard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        curr_piece.move_horizontal(-1);
        if(checkCollision()){
            curr_piece.move_horizontal(1);
        }
        this->repaint();
        break;
    case Qt::Key_Right:
        curr_piece.move_horizontal(1);
        if(checkCollision()){
            curr_piece.move_horizontal(-1);
        }
        this->repaint();
        break;
    case Qt::Key_Up:
        curr_piece.rotate(1);
        if(checkCollision()){
            curr_piece.rotate(-1);
        }
        this->repaint();
        break;
    case Qt::Key_Down:
        updateBoard();
        break;
    case Qt::Key_Space:
        instantDrop();
        break;
    }
}

void Gameboard::paintEvent(QPaintEvent *event){

    QPainter painter(this);

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            painter.setBrush(QBrush(gameboard[i][j], Qt::SolidPattern));
            painter.drawRect(QRect(j*25, i*25, 25, 25));
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(shapes[curr_piece.n][curr_piece.rotation][i][j] == 'X'){
                painter.setBrush(QBrush(piece_col[curr_piece.n], Qt::SolidPattern));
                painter.drawRect(QRect((curr_piece.x+j) * 25, (curr_piece.y+i) * 25, 25, 25));
            }

        }
    }

    if(gameOver){

    }
}
