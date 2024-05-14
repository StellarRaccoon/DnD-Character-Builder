#ifndef SHEETPAGE_H
#define SHEETPAGE_H

#include <QWidget>
#include<QtCore>
#include<QtGui>
#include<QGridLayout>
#include<QLabel>
#include"UserCharacter.h"
namespace Ui {
class SheetPage;
}

class SheetPage : public QWidget
{
    Q_OBJECT

public:
    explicit SheetPage(UserCharacter *inuserChar,QWidget *parent = nullptr);
    ~SheetPage();
    UserCharacter *userChar;

private:

    Ui::SheetPage *ui;
    //QTextDocument *document;
    //QGridLayout *gridBox;
   // QList<QLabel> *basicInfo;

};

#endif // SHEETPAGE_H
