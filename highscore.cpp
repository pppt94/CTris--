#include "highscore.h"
#include "ui_highscore.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QTextStream>
using namespace std;


highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));

    QString path = qApp->applicationDirPath() + "/scores.txt";
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while(!in.atEnd()) {
        for(int i = 0; i < 8; i++){
            QString line = in.readLine();
            QStringList list = line.split(" ");
            for(int j = 0; j < 2; j++){
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(list[j]));
            }
        }
    }

    file.close();
    lowest_it = ui->tableWidget->item(7, 1);
    lowest = lowest_it->text().toInt();
}

highscore::~highscore()
{
    delete ui;
}
