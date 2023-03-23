#ifndef SNF_SNFMULTITOOL_H
#define SNF_SNFMULTITOOL_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SnFMultitool; }
QT_END_NAMESPACE

class SnFMultitool : public QWidget {
    Q_OBJECT

public:
    explicit SnFMultitool(QWidget *parent = nullptr);
    ~SnFMultitool() override;

private:
    Ui::SnFMultitool *ui;
};


#endif //SNF_SNFMULTITOOL_H
