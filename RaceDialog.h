#ifndef RACEDIALOG_H
#define RACEDIALOG_H

#include <QDialog>
#include<QJsonArray>
#include"jsonmanipulation.h"
namespace Ui {
class RaceDialog;
}

class RaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RaceDialog(QJsonArray traitArray={}, QWidget *parent = nullptr);
    ~RaceDialog();

private:
    Ui::RaceDialog *ui;
    JsonManipulation jackson;
};

#endif // RACEDIALOG_H
