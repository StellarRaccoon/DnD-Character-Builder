#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QNetworkAccessManager>
#include<QJsonDocument>
#include<QtCore>
#include<QtGui>
#include<QTreeWidget>

//#include "secdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
