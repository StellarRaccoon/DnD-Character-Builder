/**
 * A subclass of QComboBox for ability scores
 * save the previous and current selection
*/

#ifndef SCORECOMBOBOX_H
#define SCORECOMBOBOX_H

#include <QWidget>
#include<QPlainTextEdit>
#include <QComboBox>
#include <QStandardItem>
namespace Ui {
class ScoreComboBox;
}

class ScoreComboBox : public QComboBox
{
    Q_OBJECT
private:
    //QString abilityIndex;
    QString prevScore;
    QString currentScore;

public:
        ScoreComboBox(QString cScore) {     // Constructor
        //this->abilityIndex= abilityIndex;
        this->prevScore=cScore;
        this->currentScore=cScore;
    }
    QString getPrevScore(){return this->prevScore;}
    QString getCurrentScore(){return this->currentScore;}
    //QString getAbilityIndex(){return this->abilityIndex;}

    void setPrevScore(QString prevScore){this->prevScore=prevScore;}
    void setCurrentScore(QString currentScore){this->currentScore=currentScore;}
};
#endif // SCORECOMBOBOX_H
