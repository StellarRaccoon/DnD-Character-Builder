#ifndef DIALOGTRAITS_H
#define DIALOGTRAITS_H

#include "jsonmanipulation.h"
#include <QDialog>
#include<QJsonDocument>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, QString="",QJsonArray traitArray={});
    ~Dialog();

private:
    Ui::Dialog *ui;
    JsonManipulation jackson;
};

#endif // DIALOGTRAITS_H
