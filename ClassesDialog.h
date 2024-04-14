#ifndef CLASSESDIALOG_H
#define CLASSESDIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include "jsonmanipulation.h"

namespace Ui {
class ClassesDialog;
}

class ClassesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassesDialog(QString className = "",
                           QWidget *parent = nullptr,
                           QJsonArray classArray = {});
    ~ClassesDialog();

private:
    Ui::ClassesDialog *ui;
    JsonManipulation jackson;
};

#endif // CLASSESDIALOG_H
