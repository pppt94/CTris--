#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include "piece.h"


class Gameboard : public QMainWindow
{
    Q_OBJECT

public:
    Gameboard(QWidget *parent = nullptr);
    ~Gameboard();

    virtual void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void createBoard();
    bool checkCollision();
    void lockPiece();
    void clearRows();

    QColor gameboard[20][10];
    QTimer *timer;
    Piece curr_piece;

public slots:
    void updateBoard();


};

#endif // GAMEBOARD_H
