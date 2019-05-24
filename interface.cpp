#include "interface.h"
#include "gameboard.h"
#include <QLabel>
#include <QGridLayout>
#include <QLCDNumber>


Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* contents = new QWidget(this);
    setCentralWidget(contents);

    m_board = new Gameboard(contents);

    m_score = new QLCDNumber(5);
    m_next = new QLCDNumber(5);
    m_line = new QLCDNumber(5);
    //m_board->set;


    QGridLayout* layout = new QGridLayout(contents);

    layout->addWidget(new QLabel(tr("Next Piece"), contents), 0, 0, Qt::AlignCenter);
    layout->addWidget(m_next, 1, 0);
    layout->addWidget(new QLabel(tr("Clear Lines"), contents), 2, 0, Qt::AlignCenter);
    layout->addWidget(m_score, 3, 0);
    layout->addWidget(new QLabel(tr("Next Piece"), contents), 4, 0, Qt::AlignCenter);
    layout->addWidget(m_line, 5, 0);
    //layout->addWidget(m_board, 1, 1, 5, 5);
m_board->setGeometry(QRect(0, 0, 200, 600));
    setWindowTitle(tr("C-tris ++"));
    resize(800, 600);
}

Interface::~Interface()
{

}