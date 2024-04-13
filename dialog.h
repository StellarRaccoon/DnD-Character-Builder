#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QJsonObject>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, QJsonObject *dataObj=new QJsonObject());
    ~Dialog();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
