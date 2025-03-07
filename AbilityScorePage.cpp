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

    comboOptions<<"0"<<"8"<<"10"<<"12"<<"13"<<"14"<<"15";
    userScores= updatedScores;
    //add the combo boxes to the screen

    // scoreModel = new QStandardItemModel;
    // scoreModel->appendRow(new QStandardItem("0"));
    // scoreModel->appendRow(new QStandardItem("8"));
    // scoreModel->appendRow(new QStandardItem("10"));
    // scoreModel->appendRow(new QStandardItem("12"));
    // scoreModel->appendRow(new QStandardItem("13"));
    // scoreModel->appendRow(new QStandardItem("14"));
    // scoreModel->appendRow(new QStandardItem("15"));

    ScoreComboBox *chaScoreBox = new ScoreComboBox(0,"0");
    ScoreComboBox *conScoreBox = new ScoreComboBox(1,"0");
    ScoreComboBox *dexScoreBox = new ScoreComboBox(2,"0");
    ScoreComboBox *intScoreBox = new ScoreComboBox(3,"0");
    ScoreComboBox *strScoreBox = new ScoreComboBox(4,"0");
    ScoreComboBox *wisScoreBox = new ScoreComboBox(5,"0");

    // chaScoreBox->setModel(scoreModel);
    // conScoreBox->setModel(scoreModel);
    // dexScoreBox->setModel(scoreModel);
    // intScoreBox->setModel(scoreModel);
    // strScoreBox->setModel(scoreModel);
    // wisScoreBox->setModel(scoreModel);

    ui->scoreBoxLayout->addWidget(chaScoreBox);
    ui->scoreBoxLayout->addWidget(conScoreBox);
    ui->scoreBoxLayout->addWidget(dexScoreBox);
    ui->scoreBoxLayout->addWidget(intScoreBox);
    ui->scoreBoxLayout->addWidget(strScoreBox);
    ui->scoreBoxLayout->addWidget(wisScoreBox);
    boxes<<chaScoreBox<<conScoreBox<<dexScoreBox<<intScoreBox<<strScoreBox<<wisScoreBox;

    for(auto scoreBox:boxes){

        scoreBox->addItems(comboOptions);
        connect(scoreBox, &ScoreComboBox::currentTextChanged, this,[this, scoreBox](){this->on_comboBox_text_changed(scoreBox->getIndex(), scoreBox->currentIndex());});
    }
}

/**
 * @brief Update all avalible score options when a score has been selected
 * @param boxIndex the scoreComboBox's index in the boxes array
 * @param scoreIndex the place of the score option the user has selected
 */
void AbilityScorePage::on_comboBox_text_changed(int boxIndex, int scoreIndex)
{
    QString score = boxes[boxIndex]->itemText(scoreIndex); //score value selected by user

    //update the previous and current score attributes of the combobox at the box index
    boxes[boxIndex]->setPrevScore(boxes[boxIndex]->getCurrentScore());
    boxes[boxIndex]->setCurrentScore(score);

    qDebug()<<"Combo box Number "<<boxIndex<<" ACTIVATED";
    qDebug()<<"Combo box ACTIVATED at index: "<<scoreIndex;
    qDebug()<<"Combo box previous Score: "<<boxes[boxIndex]->getPrevScore();
    qDebug()<<"----------------------------------";

    /* remove the selected value from the list of options of all other combo boxes
     * 0 should always be an option
     * any score not selected should be readded to the possible options
     */
    for(auto box:boxes){
        if(box->getIndex()!=boxIndex){
            if(score!="0"){
                //remove from other boxes
                box->removeItem(box->findText(score));
            }
            //add options back once free
            if(boxes[boxIndex]->getPrevScore()!="0"){
                box->addItem(boxes[boxIndex]->getPrevScore());
            }
        }
    }
}

AbilityScorePage::~AbilityScorePage()
{
    delete ui;
}

