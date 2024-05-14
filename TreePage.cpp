#include "TreePage.h"
#include "ui_TreePage.h"
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include"jsonmanipulation.h"
#include"RaceDialog.h"
#include<QString>
#include<ClassesDialog.h>
TreePage::TreePage(QString name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TreePage)
{
    ui->setupUi(this);


    /*create the main tree
    * column 0 is the name of the page
    * column 1 is hidden and contains the url of the item(race)
    */
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setColumnHidden(1,true);
    ui->treeWidget->setHeaderLabels(QStringList()<<name);
    this->pageTitle=name;

}

TreePage::~TreePage()
{
    delete ui;
}

/**
 * Add Root to a tree
 * @param name - text displayed in column 0 of child
 * @param description - text displayed in column 1 of child
*/

void TreePage::AddRoot(QString name, QString description){
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name); //name in column0
    itm->setText(1,description);
    ui->treeWidget->addTopLevelItem(itm);

}
/**
 * Add a child to a tree root
 * @param *parent - root thee child is under
 * @param name - text displayed in column 0 of child
 * @param description - text displayed in column 1 of child
*/
void TreePage::addChild(QTreeWidgetItem *parent, QString name, QString description){
    //create a the child item
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);

    //set the text of the child
    itm->setText(0, name); //name in column0
    itm->setText(1,description);

    //add child to the parent
    parent->addChild(itm);

}
void TreePage::populateTree(QString apiUrl){
    //should probably do something if these fail (like try again)
    //put "results" into an array, jsonArrayRaceNames is now an array of JSon objects
    QJsonArray jsonArrayRaceNames=jason.getArrayFromJson("results",jason.fetchData(apiUrl));

    //Create an tree root for every race name object in the array
    for(auto raceNames: jsonArrayRaceNames){
        //turn the current array item into an object
        QJsonObject raceNameData = raceNames.toObject();
        //select the race-name and race-url from the current object
        QString raceName = raceNameData.value("name").toString();
        QString raceUrl = raceNameData.value("url").toString();
        //add a new root to the tree
        QTreeWidgetItem *raceRoot= new QTreeWidgetItem(ui->treeWidget);
        //set the text of the item
        raceRoot->setText(0,raceName);
        raceRoot->setText(1,raceUrl);

        //qDebug()<<"url:"<<raceRoot->text(0);
    }

}
void TreePage::setCurrentItem(QString itemName){
    this->currentItem = itemName;
}
QString TreePage::getCurrentItem(){
    qDebug()<<"current item got"<<ui->treeWidget->currentItem()->text(1);
    return ui->treeWidget->currentItem()->text(1);
}
void TreePage::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //get the race name from the tree item
    QString itemName = item->text(0);
    QString title=this->objectName();
    qDebug()<<"Clicked page title: "<<this->objectName();
    /**TODO: Simplify this*/
    QJsonDocument jsonDoc;
    if(!QString::compare(title, "racePage")){
        //get the names and urls of the traits belonging to a race
        //call to race\traits which returns all the traits of a race{"count": numberofTraits, "results":[{"index":traits-index, "name":trait-name, "url":trait-url}]}
        QJsonDocument jsonDoc=jason.fetchData(item->text(1).append("/traits"));
        QJsonArray traitsArray = jason.getArrayFromJson("results",jsonDoc);
       // qDebug()<<"racial-trait url:"<<item->text(1).append("/traits");
        //create a new racial trait dialog box
        RaceDialog infoDialog(traitsArray);
        //block the main page from being acceses
        infoDialog.setModal(true);
        //launch dialog box
        infoDialog.exec();
    }

    else if(!QString::compare(title, "classPage")){
        //get the names and urls of the traits belonging to a race
        //call to get the JSON object of the class
        QJsonObject classObj= jason.fetchData(item->text(1)).object();
        QString spellcast="n/a";
        if(classObj.contains("spellcasting")){
            spellcast = classObj.value("spellcasting").toObject().value("spellcasting_ability").toString();

        }

        QJsonArray savingThrows = classObj.value("saving_throws").toArray();
        QString savingThrowStr="";
        for (int i = 0; i < savingThrows.size(); ++i) {
            QString stStr= savingThrows.at(i).toObject().value("name").toString();
            savingThrowStr.append(stStr+" ");
        }
        ClassesDialog classInfoDialog(classObj.value("name").toString(),spellcast, classObj.value("hit_die").toInt(), savingThrowStr);

        classInfoDialog.setModal(true);
        //launch dialog box
        classInfoDialog.exec();


    }
}

