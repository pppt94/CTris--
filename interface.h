#ifndef Interface_H
#define INTERFACE_H


#include <QMainWindow>
#include <iostream>
#include "piece.h"
#include "gameboard.h"

class QLabel;
class QLCDNumber;

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    QLabel* m_level;
    QLCDNumber* m_score;
    QLCDNumber* m_line;
    QLCDNumber* m_next;
    Gameboard* m_board;
};

#endif // INTERFACE_H
