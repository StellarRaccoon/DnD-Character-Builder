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
#include<QStackedWidget>
#include"AbilityScorePage.h"
//#include"SheetPage.h"
#include"extrasPage.h"


//class QPushButton;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Main Window Consturctor
    */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int currentIndex;
    UserCharacter *userCharacter;
    QStackedWidget *stackedWidget;

private slots:

    void on_nextPageButton_clicked();
    void on_backPageButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    TreePage *classPage;
    TreePage *racePage;
    AbilityScorePage *scorePage;
    extrasPage *extraInfoPage;
    //SheetPage *docPage;
};
#endif // MAINWINDOW_H
