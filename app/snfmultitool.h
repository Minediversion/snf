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
};

class SnFMultitool : public QWidget {
    Q_OBJECT

public:
    explicit SnFMultitool(QWidget *parent = nullptr);
    ~SnFMultitool() override;

private slots:
    void workFile();

private:
    Ui::SnFMultitool *ui;
};


#endif //SNF_SNFMULTITOOL_H
