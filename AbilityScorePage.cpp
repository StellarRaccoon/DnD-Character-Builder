#include "AbilityScorePage.h"
#include "ui_AbilityScorePage.h"
#include<QVBoxLayout>
#include<QComboBox>
#include<QLabel>
#include<QString>
#include<QSignalMapper>
#include <QStandardItemModel>

/**⚠️⚠️TODO Add scores to Updated scores so mainwindow has access to the scores for updating*/
AbilityScorePage::AbilityScorePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AbilityScorePage)
{
    ui->setupUi(this);

    /*
     * Store the boxes in a map ability:box
     * store the raw scores in a map
     * stores total scores in a map
     * */

    comboOptions<<"0"<<"8"<<"10"<<"12"<<"13"<<"14"<<"15";
    //userScores= updatedScores;
    //add the combo boxes to the screen

    ScoreComboBox *chaScoreBox = new ScoreComboBox("0");
    ScoreComboBox *conScoreBox = new ScoreComboBox("0");
    ScoreComboBox *dexScoreBox = new ScoreComboBox("0");
    ScoreComboBox *intScoreBox = new ScoreComboBox("0");
    ScoreComboBox *strScoreBox = new ScoreComboBox("0");
    ScoreComboBox *wisScoreBox = new ScoreComboBox("0");

    ui->scoreBoxLayout->addWidget(chaScoreBox);
    ui->scoreBoxLayout->addWidget(conScoreBox);
    ui->scoreBoxLayout->addWidget(dexScoreBox);
    ui->scoreBoxLayout->addWidget(intScoreBox);
    ui->scoreBoxLayout->addWidget(strScoreBox);
    ui->scoreBoxLayout->addWidget(wisScoreBox);

    boxes.insert("cha",chaScoreBox);
    boxes.insert("con",conScoreBox);
    boxes.insert("dex",dexScoreBox);
    boxes.insert("int",intScoreBox);
    boxes.insert("str",strScoreBox);
    boxes.insert("wis",wisScoreBox);

    QMap<QString, ScoreComboBox*>::const_iterator i = boxes.constBegin(); //iterator for loop
    while (i != boxes.constEnd()) {

        i.value()->addItems(comboOptions);
        connect(i.value(), &ScoreComboBox::currentTextChanged, this,[this, i](){this->on_comboBox_text_changed(i.key(), i.value()->currentIndex());});
        //cout << i.key() << ": " << i.value() << Qt::endl;
        ++i;
    }
}

/**
 * @brief Update all avalible score options when a score has been selected
 * @param boxIndex the scoreComboBox's index in the boxes array
 * @param scoreIndex the place of the score option the user has selected
 */
void AbilityScorePage::on_comboBox_text_changed(QString boxIndex, int scoreIndex)
{
    QString score = boxes.value(boxIndex)->itemText(scoreIndex); //score value selected by user

    //update the previous and current score attributes of the combobox at the box index
    boxes.value(boxIndex)->setPrevScore(boxes.value(boxIndex)->getCurrentScore());
    boxes.value(boxIndex)->setCurrentScore(score);

    qDebug()<<"Combo box Number "<<boxIndex<<" ACTIVATED";
    qDebug()<<"Combo box ACTIVATED at index: "<<scoreIndex;
    qDebug()<<"Combo box previous Score: "<<boxes.value(boxIndex)->getPrevScore();
    qDebug()<<"----------------------------------";

    /* remove the selected value from the list of options of all other combo boxes
     * 0 should always be an option
     * any score not selected should be readded to the possible options */
    QMap<QString, ScoreComboBox*>::const_iterator i = boxes.constBegin();
    while (i != boxes.constEnd()) {
        if(i.key()!=boxIndex){
            if(score!="0"){
                //remove the option from other boxes and update the user's score
                i.value()->removeItem(i.value()->findText(score));

            }
            //add options back once free
            if(boxes.value(boxIndex)->getPrevScore()!="0"){
                i.value()->addItem(boxes.value(boxIndex)->getPrevScore());
            }
        }
        ++i;
    }


    //total score = defaultScore +currentScore - PreviousScore

}
int AbilityScorePage::getBoxScore(QString abIndex){
    return boxes.value(abIndex)->getCurrentScore().toInt();
}
AbilityScorePage::~AbilityScorePage()
{
    delete ui;
}

