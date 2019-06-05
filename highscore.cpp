#include "highscore.h"
#include "ui_highscore.h"

highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);
}

highscore::~highscore()
{
    delete ui;
}
