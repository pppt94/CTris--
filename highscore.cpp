#include "highscore.h"
#include "ui_highscore.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QTextStream>

//using namespace std;


highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));

    path = qApp->applicationDirPath() + "/scores.txt";
    update();

}

highscore::~highscore()
{
    delete ui;
}

void highscore::update()
{
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
        break;
    }

    file.close();

    lowest_it = ui->tableWidget->item(7, 1);
    lowest = lowest_it->text().toInt();

}

void highscore::sort_data(){

    QString names[9];
    int scores[9];
    path = qApp->applicationDirPath() + "/scores.txt";
    QFile file2(path);
    file2.open(QIODevice::ReadOnly);
    QTextStream in(&file2);
    while(!in.atEnd()) {
        for(int i = 0; i < 9; i++){
            QString line = in.readLine();
            QStringList list = line.split(" ");
            names[i] = list[0];
            scores[i] = list[1].toInt();
        }
    }
    file2.close();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++)
            if (scores[j] < scores[j+1]){
               int temp = scores[j];
               scores[j] = scores[j+1];
               scores[j+1] = temp;
               QString temp1 = names[j];
               names[j] = names[j+1];
               names[j+1] = temp1;
    }
    QFile file3(path);
    file3.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file3);
    for(int i = 0; i < 7; i++){
        out << names[i] << " " << scores[i] << endl;
    }
    out << names[7] << " " << scores[7];
    file3.close();


}
