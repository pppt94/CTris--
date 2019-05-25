#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include "piece.h"


class Gameboard : public QWidget
{
    Q_OBJECT

public:
    Gameboard(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void createBoard();
    bool checkCollision();
    void lockPiece();
    void clearRows();
    void instantDrop();
    void levelUp();


    QColor gameboard[20][10];
    QTimer *timer;
    Piece curr_piece;

    bool gameOver;
    bool running;
    int score;
    int level;
    int speed;
    int speed_up;

signals:
    void scoreChanged(int score);
    void levelChanged(int level);

public slots:
    void updateBoard();
    void startGame();

};

#endif // GAMEBOARD_H
