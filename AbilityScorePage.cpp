#include "AbilityScorePage.h"
#include "ui_AbilityScorePage.h"
#include<QVBoxLayout>
#include<QComboBox>
#include<QLabel>
#include<QString>
#include<QSignalMapper>

AbilityScorePage::AbilityScorePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AbilityScorePage)
{
    ui->setupUi(this);

    hbox = new QHBoxLayout();

    int i=0;
    //labels << "Dex"<<"Str"<<"int"<<"wis"<< "cha"<<"con";
    comboOptions<<"0"<<"8"<<"10"<<"12"<<"13"<<"14"<<"15";
    userScores= updatedScores;
    //add the combo boxes to the screen

    QComboBox *chaScoreBox = new QComboBox();
    QComboBox *conScoreBox = new QComboBox();
    QComboBox *dexScoreBox = new QComboBox();
    QComboBox *intScoreBox = new QComboBox();
    QComboBox *strScoreBox = new QComboBox();
    QComboBox *wisScoreBox = new QComboBox();
    ui->scoreBoxLayout->addWidget(chaScoreBox);
    ui->scoreBoxLayout->addWidget(conScoreBox);
    ui->scoreBoxLayout->addWidget(dexScoreBox);
    ui->scoreBoxLayout->addWidget(intScoreBox);
    ui->scoreBoxLayout->addWidget(strScoreBox);
    ui->scoreBoxLayout->addWidget(wisScoreBox);
    boxes<<chaScoreBox<<conScoreBox<<dexScoreBox<<intScoreBox<<strScoreBox<<wisScoreBox;

    for(auto scoreBox:boxes){
        scoreBox->addItems(comboOptions);

        //connect(newBox, &QComboBox::activated, [this,i](int index){on_comboBox_activated(index,i);});

    }



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

//maybe we can only do indexes >0 so there can be a default
//remove the optionSelected from the list
//clear all combo boxes
void AbilityScorePage::on_comboBox_activated(int optionSelected,int activeBoxIndex)
{
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
            if(i!=activeBoxIndex){
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

}

