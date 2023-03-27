#include "snfmultitool.h"
#include "ui_SnFMultitool.h"
#include "CompressionAlgorithm.h"
#include "DecompressionAlgorithm.h"

namespace fs = std::filesystem;

std::string isFileValid(const std::string&);
std::string checkConversion(const std::string&, const std::string&);

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
    QString filePath = QFileDialog::getOpenFileName(); // Get file chosen by user
    std::string fileExtension = isFileValid(filePath.toStdString()); // Check if is a valid path
    if(fileExtension.empty()) return;
    std::string convFileExtension = fileExtension==".txt"?".snf":".txt";
    ui->lineEdit->setText(filePath); // Put it in the text display in the app

    std::string formatedFilePath = fs::path(filePath.toStdString()).make_preferred().string(); // Path is given with "/" but we want "\"

    std::string convFilePath = checkConversion(formatedFilePath, convFileExtension);
    if(convFilePath.empty()) return;

    bool output;
    if(fileExtension == ".txt"){
        output = snf::CompressionAlgorithm::compressFile(formatedFilePath, convFilePath);
        if(!output) return;
        SnFMultitoolAddons::sendSuccessMessage("File has been compressed successfully in \""+convFilePath+"\"");
    }else{
        output = snf::DecompressionAlgorithm::decompressFile(formatedFilePath, convFilePath);
        if(!output) return;
        SnFMultitoolAddons::sendSuccessMessage("File has been decompressed successfully in \""+convFilePath+"\"");
        //TODO: SHOW TEXT FILE IN APP
    }
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    SnFMultitool snFMultitool;
    snFMultitool.show();

    return a.exec();
}

std::string checkConversion(const std::string &filePath, const std::string &fileExtension){
    std::size_t directory = filePath.find_last_of('\\'); // Get last occurrence of \ to get directory
    std::string conversionFilePath = filePath.substr(0, directory+1)
                              + filePath.substr(directory+1, filePath.length()-5-directory)
                              + fileExtension; // Get the theoretical path were the converted file would be

    if(fs::exists(conversionFilePath)){ // Checks if there is already a compressed file
        //Check if user wants to overwrite file
        if(!SnFMultitoolAddons::sendOverwriteMessage("Do you want to overwrite existing "+fileExtension+" file?")){
            SnFMultitoolAddons::sendErrorMessage("User denied overwriting");
            return "";
        }
        fs::remove(conversionFilePath); //Deletes previous file
    }
    return conversionFilePath;
}

std::string isFileValid(const std::string &filePath){
    if(filePath.length()>=7) { //Checks if file has at least "Drive:/.snf"
        std::string fileExtension = filePath.substr(filePath.length() - 4, 4);
        if (filePath[1] != ':') SnFMultitoolAddons::sendErrorMessage("Filepath is not a drive");  // Checks if Drive: exist
        else if (fileExtension != ".txt" && fileExtension != ".snf") SnFMultitoolAddons::sendErrorMessage("File is not recognized by the program");
        else{
            if(fs::exists(fs::path(filePath))){ // Checks if file exists
                if(!fs::is_empty(filePath)) {
                    return fileExtension; // File is valid
                }else SnFMultitoolAddons::sendErrorMessage("File is empty");
            }else SnFMultitoolAddons::sendErrorMessage("File doesn't exist");
        }
    }else SnFMultitoolAddons::sendErrorMessage("Not a valid path");
    return "";
}


// SnFMultitoolAddons QoL functions
void SnFMultitoolAddons::sendErrorMessage(const std::string& message){
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/appIcon/resources/snfLogo.png"));
    msg.setIcon(QMessageBox::Icon::Critical);
    msg.setText(QString::fromStdString(message));
    msg.setWindowTitle("Error");

    QPushButton *okbutton = msg.addButton(QMessageBox::Ok);

    msg.exec();

    if(msg.clickedButton() == okbutton){
        msg.close();
    }
}

void SnFMultitoolAddons::sendSuccessMessage(const std::string& message){
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/appIcon/resources/snfLogo.png"));
    msg.setIcon(QMessageBox::Icon::Information);
    msg.setText(QString::fromStdString(message));
    msg.setWindowTitle("Successful");

    QPushButton *okbutton = msg.addButton(QMessageBox::Ok);

    msg.exec();

    if(msg.clickedButton() == okbutton){
        msg.close();
    }
}

bool SnFMultitoolAddons::sendOverwriteMessage(const std::string& message){
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/appIcon/resources/snfLogo.png"));
    msg.setIcon(QMessageBox::Icon::Question);
    msg.setText(QString::fromStdString(message));
    msg.setWindowTitle("Overwrite");

    QPushButton *yesButton = msg.addButton(QMessageBox::Yes);
    QPushButton *noButton = msg.addButton(QMessageBox::No);

    msg.exec();
    if(msg.clickedButton() == yesButton){
        msg.close();
        return true;
    }else if(msg.clickedButton() == noButton){
        msg.close();
        return false;
    }
    return false;
}