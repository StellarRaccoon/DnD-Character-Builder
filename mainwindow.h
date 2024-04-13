#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QNetworkAccessManager>
#include<QJsonDocument>
#include<QtCore>
#include<QtGui>
#include<QTreeWidget>
#include "jsonmanipulation.h"

//#include "secdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void AddRoot(QString name, QString Description);
    void addChild(QTreeWidgetItem *parent, QString name, QString Description);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //JsonManipulation jason;
private slots:
    //void on_pushButton_clicked();

    //void on_pushButton_clicked();

    //void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    //QNetworkAccessManager manager;
    JsonManipulation jason;
    bool fetchData(QString urlPath, QJsonDocument &document);
    //int getNamesFromJson(QJsonDocument document, QJsonArray &jsonArray);
};
#endif // MAINWINDOW_H
