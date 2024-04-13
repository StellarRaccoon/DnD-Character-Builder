#include "dialogTraits.h"
#include "ui_dialogTraits.h"
#include<QJsonDocument>
#include<QJsonDocument>
#include<QBoxLayout>
#include<QPlainTextEdit>
#include<QGroupBox>
Dialog::Dialog(QWidget *parent, QString raceName, QJsonArray racialTraitArray)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    //QJsonObject dataObj = dataDoc->object();
    //jackson.getNamesFromJson(dataDoc)
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    qDebug()<<"In Dialog";
    ui->setupUi(this);
    ui->dialogTitle->setText(raceName);
    ui->dialogTitle->setReadOnly(true);

    //create a vertical layout box to add traits to the ui
    for(auto racialTrait: racialTraitArray){
        QJsonObject traitNameData = racialTrait.toObject();
        QString traitName = traitNameData.value("name").toString();
        QString traitUrl = traitNameData.value("url").toString();

        //go to the url and get the description
        QJsonDocument traitData;
        qDebug()<<"traitURL: "<<traitUrl;
        jackson.fetchData(traitUrl,traitData);

        //Get the description by turning the doc into and object, selecting the desciption key, and getting the first description in the array
        QString traitDescription=traitData.object().value("desc").toArray()[0].toString();
        qDebug()<<"trait Descript: "<<traitDescription;

        //create a new group box with label=trait name
        QGroupBox *traitBox = new QGroupBox(traitName, this);
        QVBoxLayout *traitLayout = new QVBoxLayout(traitBox);
        QPlainTextEdit *traitDescriptText = new QPlainTextEdit(traitDescription, traitBox);
        traitDescriptText->setReadOnly(true);
        traitLayout->addWidget(traitDescriptText);
        dialogLayout->addWidget(traitBox);
        /*⚠️⚠️TODO: put the description into a text box and add it to the screen with the trait box*/
        //QTreeWidgetItem *raceRoot= new QTreeWidgetItem(ui->treeWidget);
    }
    //
   // setLayout(dialogLayout);

}

Dialog::~Dialog()
{
    delete ui;
}
