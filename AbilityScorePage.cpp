#include "AbilityScorePage.h"
#include "ui_AbilityScorePage.h"
#include<QVBoxLayout>
#include<QComboBox>
#include<QLabel>
#include<QString>
#include<QSignalMapper>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QHeaderView>

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
        ++i;
    }
    //insert total tables
    QStringList headers ={"Bonus", "Total"};
    QTableWidget* chaScoreTable = new QTableWidget(2,1);
    chaScoreTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chaScoreTable->setVerticalHeaderLabels(headers);
    chaScoreTable->horizontalHeader()->hide();

    // Add items
    QTableWidgetItem *item1 = new QTableWidgetItem("Test Val");
    chaScoreTable->setItem(1, 0, item1);
    item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
    ui->totalBoxLayout->addWidget(chaScoreTable);


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
            //add options back once free in desending order
            if(boxes.value(boxIndex)->getPrevScore()!="0"){
                QString optionToAdd = boxes.value(boxIndex)->getPrevScore();
                int j=1;
                while( j<=i.value()->count()){
                    int currentOption=i.value()->itemText(j).toInt();
                    if(optionToAdd.toInt()<currentOption || currentOption==0){
                        i.value()->insertItem(j,boxes.value(boxIndex)->getPrevScore());
                        qDebug()<<"inserted at: "<<j;
                        j=i.value()->count()+1; //end search
                    }
                    j++;
                }
            }
        }
        ++i;
    }
    //int total =
    //⚠️TODO add total
    //total score = scorebonus +currentScore - PreviousScore

}
int AbilityScorePage::getBoxScore(QString abIndex){
    return boxes.value(abIndex)->getCurrentScore().toInt();
}

QMap<QString, int> AbilityScorePage::getCharAbilityBonus() const
{
    return charAbilityBonus;
}

void AbilityScorePage::setCharAbilityBonus(QString abilityIndex, int bonusValue)
{
    charAbilityBonus.insert(abilityIndex,bonusValue);
}
AbilityScorePage::~AbilityScorePage()
{
    delete ui;
}

