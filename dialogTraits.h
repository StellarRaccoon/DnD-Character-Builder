#ifndef DIALOGTRAITS_H
#define DIALOGTRAITS_H

#include <QDialog>
#include<QJsonDocument>
#include "jsonmanipulation.h"

namespace Ui {
class dialogTraits;
}

class dialogTraits : public QDialog
{
    Q_OBJECT

public:
    explicit dialogTraits(QWidget *parent = nullptr, QString="",QJsonArray traitArray={});
    ~dialogTraits();

private:
    Ui::dialogTraits *ui;
    JsonManipulation jackson;
};

#endif // DIALOGTRAITS_H
