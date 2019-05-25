#include "interface.h"
#include "gameboard.h"
#include <QtGlobal>
#include <QLabel>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>


Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* contents = new QWidget(this);
    setCentralWidget(contents);



    //m_board->setGeometry(QRect(0, 0, 200, 600));
    m_score = new QLCDNumber(5);
    m_score->setFixedSize(100, 100);
    m_next = new QLabel(contents);
    m_next->setFixedSize(100, 100);
    m_next->setAutoFillBackground(true);
    {
        QPalette palette = m_next->palette();
        palette.setColor(m_next->backgroundRole(), Qt::white);
        m_next->setPalette(palette);
}
    m_line = new QLCDNumber(5);
    startButton = new QPushButton(tr("&Start"));
    pauseButton = new QPushButton(tr("&Pause"));
    scoreButton = new QPushButton(tr("&High Score"));
    quitButton = new QPushButton(tr("&Quit"));
    //m_board->set;

    m_board = new Gameboard(contents);

    connect(m_board, &Gameboard::scoreChanged, m_score, QOverload<int>::of(&QLCDNumber::display));


    QGridLayout* layout = new QGridLayout(contents);

    layout->addWidget(new QLabel(tr("Next Piece"), contents), 0, 1, Qt::AlignCenter);
    layout->addWidget(m_next, 1, 1);
    layout->addWidget(new QLabel(tr("Score"), contents), 2, 1, Qt::AlignCenter);
    layout->addWidget(m_score, 3, 1);
    layout->addWidget(new QLabel(tr("Clear Lines"), contents), 4, 1, Qt::AlignCenter);
    layout->addWidget(m_line, 5, 1);
    layout->addWidget(startButton, 6, 1);
    layout->addWidget(scoreButton, 7, 1);
    layout->addWidget(pauseButton, 8, 1);
    layout->addWidget(quitButton, 9, 1);
    layout->addWidget(m_board, 0, 0, 10, 0);

//    layout->setRowStretch(0, 1);
//    layout->setRowStretch(1, 2);
//    layout->setRowStretch(2, 1);
//    layout->setRowStretch(3, 2);
//    layout->setRowStretch(4, 1);
//    layout->setRowStretch(5, 2);
//    layout->setColumnStretch(0, 2);
//    layout->setColumnStretch(1, 1);


    setWindowTitle(tr("C-tris ++"));
    resize(400, 520);
}

Interface::~Interface()
{

}
