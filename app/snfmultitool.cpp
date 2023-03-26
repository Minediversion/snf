#include <QApplication>
#include "snfmultitool.h"
#include "ui_SnFMultitool.h"
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPushButton>

SnFMultitool::SnFMultitool(QWidget *parent) :
        QWidget(parent), ui(new Ui::SnFMultitool) {
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon(R"(C:\Users\marcr\CLionProjects\snf\app\file_open_FILL0_wght400_GRAD0_opsz48.png)"));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(findFile()));
    ui->plainTextEdit->hide();
}

SnFMultitool::~SnFMultitool() {
    delete ui;
}

void SnFMultitool::findFile(){
    ui->lineEdit->setText(QFileDialog::getOpenFileName());
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    SnFMultitool snFMultitool;
    snFMultitool.show();

    return a.exec();
}