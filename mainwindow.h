#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "TreePage.h"
#include <QMainWindow>
#include<QNetworkAccessManager>
#include<QJsonDocument>
#include<QtCore>
#include<QtGui>
#include<QTreeWidget>
#include<UserCharacter.h>
//#include "secdialog.h"
#include<QStackedWidget>
QT_BEGIN_NAMESPACE
//class QPushButton;
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
    int currentIndex;
    UserCharacter *userCharacter;
    QStackedWidget *stackedWidget;

private slots:

    void on_nextPageButton_clicked();
    void on_backPageButton_clicked();

private:
    Ui::MainWindow *ui;
    TreePage *classPage;
    TreePage *racePage;
};
#endif // MAINWINDOW_H
