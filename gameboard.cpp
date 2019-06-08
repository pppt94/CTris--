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

    timer  = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateBoard()));
    createBoard();
    high_score = new highscore(this);
    running = false;
    scoring = false;

    welcome.setText("<p align='center'><font size = 10 color = red >Welcome in the C-Tris++ Game!<br>"
                    "<font size = 6>How to play? & Game control");
    welcome.setInformativeText("<p align='center'><font size = 4>\n"
                               "The goal of Tetris is to score as many points as possible,"
                               "by clearing horizontal lines of Blocks. The player must rotate,"
                               "move, and drop the falling Tetriminos inside the Matrix (playing field)."
                               "Lines are cleared when they are filled with Blocks and have no empty spaces."
                               "As lines are cleared, the level increases and Tetriminos fall faster,"
                               "making the game progressively more challenging. If the Blocks land above"
                               "the top of the playing field, the game is over.<br>"
                               "<br>"
                               "Left&Right&Down Arrow -> move block <br>"
                               "Space -> instant drop");
    welcome.show();
}

void Gameboard::startGame()
{
    createBoard();
    curr_piece.resetPiece();
    score = 0;
    level = 1;
    speed = 400;
    speed_up = 50;
    timer->start(speed);
    emit levelChanged(level);
    running = true;
}

void Gameboard::pauseGame()
{
    if (running) {
        timer->stop();
        running = false;
    } else {
        timer->start(speed);
        running = true;
    }
}

void Gameboard::showScore()
{
    running = false;
    high_score->show();
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
    if(running){
        curr_piece.move_vertical(1);
        if(checkCollision()){
            curr_piece.move_vertical(-1);
            lockPiece();
            if(checkFull()){
                endGame();
            }

            curr_piece.resetPiece();
        }
        clearRows();
        this->repaint();
    }
}

void Gameboard::endGame(){
    startGame();
}

bool Gameboard::checkFull()
{
    for(int i = 0; i < 10; i++){
        if(gameboard[0][i] != QColor(Qt::white))
            return true;
    }
    return false;
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

    score += rowsCount*10;
    emit scoreChanged(score);
    if(rowsCount){
        levelUp();
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

void Gameboard::levelUp()
{
    if(score%50==0 && score != 0){
        level++;
        emit levelChanged(level);
        speed -= speed_up;
        timer->start(speed);
    }
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

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(shapes[curr_piece.next_n][0][i][j] == 'X'){
                painter.setBrush(QBrush(piece_col[curr_piece.next_n], Qt::SolidPattern));
                painter.drawRect(QRect((j * 25)+280, (i * 25)+50, 25, 25));
            }

        }
    }

    if(gameOver){

    }
}
