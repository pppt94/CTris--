#ifndef Interface_H
#define INTERFACE_H


#include <QMainWindow>
#include <iostream>
#include "piece.h"
#include "gameboard.h"

class QLabel;
class QLCDNumber;
class QPushButton;
class QtGlobal;

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    QLCDNumber* m_score;
    QLCDNumber* m_level;
    QLabel* m_next;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *scoreButton;
    QPushButton *quitButton;
    Gameboard* m_board;


};

#endif // INTERFACE_H
