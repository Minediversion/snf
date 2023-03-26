#include <QApplication>
#include "snfmultitool.h"
#include "ui_SnFMultitool.h"
#include <QFileDialog>
#include "CompressionAlgorithm.h"
#include "DecompressionAlgorithm.h"

namespace fs = std::filesystem;

std::string isFileValid(const std::string&);

SnFMultitool::SnFMultitool(QWidget *parent) :
        QWidget(parent), ui(new Ui::SnFMultitool) {
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon(":/fileOpen/resources/file_open.png"));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(workFile()));
    ui->plainTextEdit->hide();
}

SnFMultitool::~SnFMultitool() {
    delete ui;
}

void SnFMultitool::workFile(){
    QString filePath = QFileDialog::getOpenFileName();
    ui->lineEdit->setText(filePath);
    std::string fileExtension = isFileValid(filePath.toStdString());
    if(fileExtension.empty()){ // TODO: Show error message
        ui->lineEdit->setText("");
        return;
    }
    fs::path formatedFilePath = filePath.toStdString();
    int output;
    if(fileExtension == ".txt"){
        snf::CompressionAlgorithm compressionAlgorithm;
        output = compressionAlgorithm.compressFile(formatedFilePath.make_preferred().string());
    }else{
        snf::DecompressionAlgorithm decompressionAlgorithm;
        output = decompressionAlgorithm.decompressFile(formatedFilePath.make_preferred().string());
    }
    if(output); // Show output location
    else; // Show error message

}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    SnFMultitool snFMultitool;
    snFMultitool.show();

    return a.exec();
}

std::string isFileValid(const std::string &filePath){
    if(filePath.length()>=7) { //Checks if file has at least "Drive:/.snf"
        std::string fileExtension = filePath.substr(filePath.length() - 4, 4);
        if (filePath[1] != ':') std::cout << "Filepath is not a drive" << std::endl;  // Checks if Drive: exist
        else if (fileExtension != ".txt" && fileExtension != ".snf") std::cout << "File is not recognized by the program" << std::endl;
        else{
            if(fs::exists(fs::path(filePath))){ // Checks if file exists
                if(!fs::is_empty(filePath)) {
                    std::cout << "Valid file" << std::endl;
                    return fileExtension;
                }else std::cout << "File is empty" << std::endl;
            }else std::cout << "File doesn't exist" << std::endl;
        }
    }else std::cout << "Not a valid path" << std::endl;
    return "";
}