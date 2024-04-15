#include "RaceDialog.h"
#include "ui_RaceDialog.h"
#include<QVBoxLayout>
#include<QGroupBox>
#include<QPlainTextEdit>
RaceDialog::RaceDialog(QString raceName,QJsonArray traitArray,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RaceDialog)
{

    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    qDebug()<<"In Dialog";
    ui->setupUi(this);
    ui->pageTitle->setText(raceName);


    //create a vertical layout box to add traits to the ui
    for(auto racialTrait: traitArray){
        QJsonObject traitNameData = racialTrait.toObject();
        QString traitName = traitNameData.value("name").toString();
        QString traitUrl = traitNameData.value("url").toString();

        //go to the url and get the description

        qDebug()<<"traitURL: "<<traitUrl;
        QJsonDocument traitData=jackson.fetchData(traitUrl);

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


RaceDialog::~RaceDialog()
{
    delete ui;
}
