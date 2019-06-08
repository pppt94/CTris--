#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>
#include <QInputDialog>
#include <iostream>
#include "piece.h"
#include "highscore.h"


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
    bool checkFull();
    void endGame();
    void saveScore();


    QColor gameboard[20][10];
    QTimer *timer;
    highscore *high_score;
    Piece curr_piece;

    QMessageBox welcome;
    QMessageBox end;

    bool gameOver;
    bool running;
    bool scoring;
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
    void pauseGame();
    void showScore();

};

#endif // GAMEBOARD_H
