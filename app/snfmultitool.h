#ifndef SNF_SNFMULTITOOL_H
#define SNF_SNFMULTITOOL_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QTableWidget>
#include <QMenuBar>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class SnFMultitool; }
QT_END_NAMESPACE

class SnFMultitoolAddons{
    public:
        static void sendErrorMessage(const std::string& message);
        static void sendSuccessMessage(const std::string& message);
        static bool sendOverwriteMessage(const std::string &message);
        static std::string checkConversion(const std::string &filePath, const std::string &fileExtension);
        static std::string isFileValid(const std::string &filePath);
};

class SnFMultitool : public QWidget {
    Q_OBJECT

public:
    explicit SnFMultitool(QWidget *parent = nullptr);
    ~SnFMultitool() override;
    void workFileOpenSnf(const std::string &filePath);

private slots:
    void workFile();

private:
    Ui::SnFMultitool *ui;
};


#endif //SNF_SNFMULTITOOL_H
