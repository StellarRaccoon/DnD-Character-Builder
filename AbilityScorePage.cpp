#include "AbilityScorePage.h"
#include "ui_AbilityScorePage.h"
#include<QVBoxLayout>
#include<QComboBox>
#include<QLabel>
#include<QString>
#include<QSignalMapper>
#include <QStandardItemModel>
AbilityScorePage::AbilityScorePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AbilityScorePage)
{
    ui->setupUi(this);

    hbox = new QHBoxLayout();


    //labels << "Dex"<<"Str"<<"int"<<"wis"<< "cha"<<"con";
    comboOptions<<"0"<<"8"<<"10"<<"12"<<"13"<<"14"<<"15";
    userScores= updatedScores;
    //add the combo boxes to the screen

    scoreModel = new QStandardItemModel;
    scoreModel->appendRow(new QStandardItem("0"));
    scoreModel->appendRow(new QStandardItem("8"));
    scoreModel->appendRow(new QStandardItem("10"));
    scoreModel->appendRow(new QStandardItem("12"));
    scoreModel->appendRow(new QStandardItem("13"));
    scoreModel->appendRow(new QStandardItem("14"));
    scoreModel->appendRow(new QStandardItem("15"));

    QComboBox *chaScoreBox = new QComboBox();
    QComboBox *conScoreBox = new QComboBox();
    QComboBox *dexScoreBox = new QComboBox();
    QComboBox *intScoreBox = new QComboBox();
    QComboBox *strScoreBox = new QComboBox();
    QComboBox *wisScoreBox = new QComboBox();

    chaScoreBox->setModel(scoreModel);
    conScoreBox->setModel(scoreModel);
    dexScoreBox->setModel(scoreModel);
    intScoreBox->setModel(scoreModel);
    strScoreBox->setModel(scoreModel);
    wisScoreBox->setModel(scoreModel);

    ui->scoreBoxLayout->addWidget(chaScoreBox);
    ui->scoreBoxLayout->addWidget(conScoreBox);
    ui->scoreBoxLayout->addWidget(dexScoreBox);
    ui->scoreBoxLayout->addWidget(intScoreBox);
    ui->scoreBoxLayout->addWidget(strScoreBox);
    ui->scoreBoxLayout->addWidget(wisScoreBox);
    boxes<<chaScoreBox<<conScoreBox<<dexScoreBox<<intScoreBox<<strScoreBox<<wisScoreBox;

    // for(auto scoreBox:boxes){

    //     scoreBox->addItems(comboOptions);
    //     connect(scoreBox, SIGNAL(activated(int)), this,SLOT(on_comboBox_activated(int)));
    //     connect(scoreBox, SIGNAL(currentTextChanged(QString)), this,SLOT(on_score_selected(QString)));
    // }

    connect(chaScoreBox, SIGNAL(activated(int)), this,SLOT(on_comboBox_activated(int)));
    connect(chaScoreBox, SIGNAL(currentTextChanged(QString)), this,SLOT(on_score_selected(QString)));

}

/**
 * ⚠️⚠️TODO
 * Get the comboboxes working
 * disable currently used options
 * should update the list of each box when a selection is made (textActivate signal, currentIndexChanged, or currentTextChanged)
 *
 */

AbilityScorePage::~AbilityScorePage()
{
    delete ui;
}
void AbilityScorePage::on_score_selected(QString score){
    //get the index of that score
    //remove the index
    qDebug()<<"Current text changed to: "<<score;

}
//maybe we can only do indexes >0 so there can be a default
//remove the optionSelected from the list
//clear all combo boxes
void AbilityScorePage::on_comboBox_activated(int index)
{
    qDebug()<<"Combo box ACTIVATED at index: "<<index;
    /*
    QComboBox *selectedBox=boxes.at(activeBoxIndex);

    QString prev= m_previousText[selectedBox];
    //get the selected option
    QString option=selectedBox->itemText(optionSelected);
    qDebug()<<"Option Selected: "<<option;
    if(QString::compare(option,"0")!=0){ //if 0 is not selected (if zero was selected compare==0)
        int i=0;
            //remove that option from currentOptions

        for(auto box:boxes){
            //find the current selection of each box
            //remove that item
            if(i!=activeBoxconnect(scoreBox, SIGNAL(currentIndexChanged(int)), this,SLOT(on_score_selected(int)));Index){
                int atIndex = box->findText(option);
                box->removeItem(atIndex);
            }
            i++;
        }
        //set the updated score
        updatedScores.setFromIndex(labels[activeBoxIndex],option.toInt());
        qDebug()<<"setting score Selected: "<<updatedScores.getValueFromIndex(labels[activeBoxIndex]);
    }
    //if the item 0 was selected, add back in the option
    //get
    else if(QString::compare(option,"0")==0){
        //get the text of the option
        int indexInList=comboOptions.indexOf(option);
        int i=0;
        for(auto box:boxes){
            if(i!=activeBoxIndex){
                box->insertItem(indexInList,prev);

            }
            i++;
        }
    }
    m_previousText[selectedBox] = boxes.at(activeBoxIndex)->currentText();

    int i=0;


    for(QString label:labels){
        int score = boxes.at(i)->itemText(i).toInt();
        score = userScores.getValueFromIndex(label)+score;
        QString scoreStr = QString("Total: %1").arg(score);
        totalScores.at(i)->setText(scoreStr);

        qDebug()<<"updated Score "<<label<<": "<<updatedScores.getValueFromIndex(label);
    }
*/
}

