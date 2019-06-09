#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>
#include <QFile>
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
    void update();
    void sort_data();
    QString path;

private:
    Ui::highscore *ui;
};

#endif // HIGHSCORE_H
