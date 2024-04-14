#ifndef TREEPAGE_H
#define TREEPAGE_H

#include <QWidget>
#include<QPlainTextEdit>
#include<QTreeWidget>
#include<QVBoxLayout>
#include"jsonmanipulation.h"
namespace Ui {
class TreePage;
}

class TreePage : public QWidget
{
    Q_OBJECT

public:
    explicit TreePage(QString name="",QWidget *parent = nullptr);
    ~TreePage();
    QTreeWidget mainTree;
    void populateTree(QString apiUrl);
    void setCurrentItem(QString itemName);
    QString getCurrentItem();


private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::TreePage *ui;
    void addChild(QTreeWidgetItem *parent, QString name, QString description);
    void AddRoot(QString name, QString description);
    void buildTreeRoots();
    QVBoxLayout *pageLayout;
    QString pageTitle;
    JsonManipulation jason;
    QString currentItem;

};

#endif // TREEPAGE_H

