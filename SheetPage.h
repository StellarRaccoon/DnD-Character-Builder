#ifndef SHEETPAGE_H
#define SHEETPAGE_H

#include <QWidget>
#include<QTextDocument>
namespace Ui {
class SheetPage;
}

class SheetPage : public QWidget
{
    Q_OBJECT

public:
    explicit SheetPage(QWidget *parent = nullptr);
    ~SheetPage();

private:
    Ui::SheetPage *ui;
    //QTextDocument *document;
};

#endif // SHEETPAGE_H
