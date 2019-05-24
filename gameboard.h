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

    QColor gameboard[20][10];
    QTimer *timer;
    Piece curr_piece;

    bool gameOver;

public slots:
    void updateBoard();

};

#endif // GAMEBOARD_H
