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
      "....."
      ".XX..",
      ".XX..",
      "....."},
     {".....",
      "....."
      ".XX..",
      ".XX..",
      "....."},
     {".....",
      "....."
      ".XX..",
      ".XX..",
      "....."},
     {".....",
      "....."
      ".XX..",
      ".XX..",
      "....."}},
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
    : QMainWindow(parent)
{

    createBoard();
    timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateBoard()));
    timer->start(1000);
    //timer->setInterval(50);
}

Gameboard::~Gameboard()
{

}

void Gameboard::createBoard(){

    for(int i = 0; i < 200; i++){
            gameboard[i] = QColor(Qt::white);
    }
}

void Gameboard::updateBoard()
{
    curr_piece.move_vertical();
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
            }
        }
    }
    return false;
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
        curr_piece.rotate();
        this->repaint();
        break;
    }
}

void Gameboard::paintEvent(QPaintEvent *event){

    QPainter painter(this);

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            painter.setBrush(QBrush(gameboard[i*10 + j], Qt::SolidPattern));
            painter.drawRect(QRect(j*20, i*20, 20, 20));
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(shapes[curr_piece.n][curr_piece.rotation][i][j] == 'X'){
                painter.setBrush(QBrush(piece_col[curr_piece.n], Qt::SolidPattern));
                painter.drawRect(QRect((curr_piece.x+j) * 20, (curr_piece.y+i) * 20, 20, 20));
            }

        }
    }
}
