#include <QApplication>
#include "snfmultitool.h"
#include "ui_SnFMultitool.h"

SnFMultitool::SnFMultitool(QWidget *parent) :
        QWidget(parent), ui(new Ui::SnFMultitool) {
    ui->setupUi(this);
}

SnFMultitool::~SnFMultitool() {
    delete ui;
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QWidget widget;
    widget.show();
    return a.exec();
}