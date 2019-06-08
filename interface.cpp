#include "interface.h"
#include "gameboard.h"
#include <QtGlobal>
#include <QLabel>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QApplication>


Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* contents = new QWidget(this);
    setCentralWidget(contents);



    //m_board->setGeometry(QRect(0, 0, 200, 600));
    m_score = new QLCDNumber(5);
    m_next = new QLabel(contents);
    m_next->setFixedSize(140, 140);
    m_next->setAutoFillBackground(true);
    {
        QPalette palette = m_next->palette();
        palette.setColor(m_next->backgroundRole(), Qt::white);
        m_next->setPalette(palette);
}
    m_level = new QLCDNumber(5);
    startButton = new QPushButton(tr("&Start Game"));
    pauseButton = new QPushButton(tr("&Pause/Resume"));
    scoreButton = new QPushButton(tr("&High Score"));
    quitButton = new QPushButton(tr("&Quit"));
    //m_board->set;

    m_board = new Gameboard(contents);

    connect(startButton, &QPushButton::clicked, m_board, &Gameboard::startGame);
    connect(scoreButton, &QPushButton::clicked, m_board, &Gameboard::showScore);
    connect(pauseButton, &QPushButton::clicked, m_board, &Gameboard::pauseGame);
    connect(quitButton , &QPushButton::clicked, this, &QApplication::quit);

    connect(m_board, &Gameboard::scoreChanged, m_score, QOverload<int>::of(&QLCDNumber::display));
    connect(m_board, &Gameboard::levelChanged, m_level, QOverload<int>::of(&QLCDNumber::display));





    QGridLayout* layout = new QGridLayout(contents);

    layout->addWidget(new QLabel(tr("<font size = 5 color = red>Next Piece"), contents), 0, 1, Qt::AlignCenter);
    layout->addWidget(m_next, 1, 1);
    layout->addWidget(new QLabel(tr("<font size = 5 color = red>Score"), contents), 2, 1, Qt::AlignCenter);
    layout->addWidget(m_score, 3, 1);
    layout->addWidget(new QLabel(tr("<font size = 5 color = red>Level"), contents), 4, 1, Qt::AlignCenter);
    layout->addWidget(m_level, 5, 1);
    layout->addWidget(startButton, 7, 1);
    layout->addWidget(scoreButton, 8, 1);
    layout->addWidget(pauseButton, 9, 1);
    layout->addWidget(quitButton, 10, 1);
    layout->addWidget(m_board, 0, 0, 10, 0);



    setWindowTitle(tr("C-Tris ++"));
    resize(440, 550);
}

Interface::~Interface()
{

}
