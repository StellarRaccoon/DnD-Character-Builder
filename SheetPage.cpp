#include "SheetPage.h"
#include "ui_SheetPage.h"
#include<QTextDocument>
#include<QVBoxLayout>
#include<QTextEdit>
SheetPage::SheetPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SheetPage)
{
     ui->setupUi(this);
    // QVBoxLayout *layout = new QVBoxLayout(this);
    // auto *textEdit = new QTextEdit();
    // QString html =
    //     "<div align=right>"
    //     "City, 11/11/2015"
    //     "</div>"
    //     "<div align=left>"
    //     "Sender Name<br>"
    //     "street 34/56A<br>"
    //     "121-43 city"
    //     "</div>"
    //     "<h1 align=center>DOCUMENT TITLE</h1>"
    //     "<p align=justify>"
    //     "document content document content document content document content document content document content document content document content document content document content "
    //     "document content document content document content document content document content document content document content document content document content document content "
    //     "</p>"
    //     "<div align=right>sincerly</div>";


    // document->setHtml(html);

    // textEdit->setDocument(document);
    //layout->addWidget(textEdit);
}

SheetPage::~SheetPage()
{
    delete ui;
}
