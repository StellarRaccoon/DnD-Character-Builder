#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "secdialog.h"
#include<QLabel>
#include<QNetworkReply>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include "TreePage.h"

/**
 * Main Window Consturctor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*insert a page into the stacked widget*/
    QHBoxLayout *layout = new QHBoxLayout;
    TreePage *newForm=new TreePage("Race");
    layout->addWidget(newForm);
    ui->stackedWidget->insertWidget(0,newForm);
    newForm->populateTree("/api/races");

}

/**
 * Main Window Destructor
*/
MainWindow::~MainWindow()
{
    delete ui;
}

