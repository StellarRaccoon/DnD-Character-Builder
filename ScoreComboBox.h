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
    int index;
    QString prevScore;
    QString currentScore;

public:
        ScoreComboBox(int i, QString cScore) {     // Constructor
        this->index = i;
        this->prevScore=cScore;
        this->currentScore=cScore;
    }
    QString getPrevScore(){return this->prevScore;}
    QString getCurrentScore(){return this->currentScore;}
    int getIndex(){return this->index;}

    void setPrevScore(QString prevScore){this->prevScore=prevScore;}
    void setCurrentScore(QString currentScore){this->currentScore=currentScore;}
};
#endif // SCORECOMBOBOX_H
