#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
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

    QColor gameboard[20*10];
    Piece curr_piece;
};

#endif // GAMEBOARD_H
