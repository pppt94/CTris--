#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>
#include <QTableWidgetItem>


namespace Ui {
class highscore;
}

class highscore : public QDialog
{
    Q_OBJECT

public:
    explicit highscore(QWidget *parent = nullptr);
    ~highscore();
    QTableWidgetItem * lowest_it;
    int lowest;

private:
    Ui::highscore *ui;
};

#endif // HIGHSCORE_H
