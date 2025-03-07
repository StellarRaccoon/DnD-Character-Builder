#ifndef SCORECOMBOBOX_H
#define SCORECOMBOBOX_H


#include <QWidget>
#include<QPlainTextEdit>
#include <QComboBox>

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
        ScoreComboBox(int i, QString currentScore) {     // Constructor
        this->index = i;
        this->currentScore = currentScore;
        this->prevScore = currentScore;
    }

    QString getPrevScore(){return this->prevScore;}
    QString getCurrentScore(){return this->currentScore;}
    int getIndex(){return this->index;}

    void setPrevScore(QString prevScore){this->prevScore=prevScore;}
    void setCurrentScore(QString currentScore){this->currentScore=currentScore;}
    void setIndex(int index){this->index=index;}
};
#endif // SCORECOMBOBOX_H
