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
    labels << "Dex"<<"Str"<<"int"<<"wis"<< "cha"<<"con";
    comboOptions<<"0"<<"8"<<"10"<<"12"<<"13"<<"14"<<"15";
    userScores= updatedScores;
    for(auto label:labels){
        QVBoxLayout *vbox = new QVBoxLayout();
        //create a combo box
        QComboBox *newBox =new QComboBox();
        newBox->objectName()=label;
        //add the options into the box
        newBox->insertItems(0,comboOptions);
        //create a label
        QLabel *labelItem = new QLabel();
        QLabel *totalItem = new QLabel();
        totalItem->setText("Total Score: ");
        totalScores.append(totalItem);

        labelItem->setText(label);

        m_previousText[newBox] = newBox->currentText();
        connect(newBox, &QComboBox::activated, [this,i](int index){on_comboBox_activated(index,i);});
        //add to the layout
        boxes.append(newBox);
        vbox->addWidget(labelItem);
        vbox->addWidget(newBox);
        vbox->addWidget(totalItem);
        i++;
        hbox->addItem(vbox);
    }
    this->setLayout(hbox);


}



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
    //int prevTextIndex=selectedBox->indexOf(m_previousText[selectedBox]);
    qDebug()<<"Index: "<<optionSelected;
    qDebug()<<"Box Index: "<<activeBoxIndex;
    qDebug()<<"prev Index: "<<m_previousText[boxes.at(activeBoxIndex)];
    QString prev= m_previousText[boxes.at(activeBoxIndex)];
    //get the selected option
    QString option=boxes.at(activeBoxIndex)->itemText(optionSelected);

    if(QString::compare(option,"0")!=0){
        int i=0;
            //remove that option from currentOptions

        for(auto box:boxes){
            //find the current selection of each box
            //remove that item
            if(i!=activeBoxIndex){
                int atIndex = box->findText(option);

                qDebug()<<"removing item at: "<<atIndex<<" from box: "<<i;
                box->removeItem(box->findText(option));
            }
            i++;
        }
    }
    //if the item 0 was selected, add back in the option
    //get
    else if(QString::compare(option,"0")==0){
        //get the text of the option
        int indexInList=comboOptions.indexOf(option);
        int i=0;
        for(auto box:boxes){
            if(i!=activeBoxIndex){
                qDebug()<<"Adding in: "<<prev<< " at index: "<<indexInList<<" for box: "<<i;
                //add to the back if the index in list >num of option
                //int numOfOption=box->count();

                box->insertItem(indexInList,prev);

            }
            i++;
        }
    }
    m_previousText[boxes.at(activeBoxIndex)] = boxes.at(activeBoxIndex)->currentText();

    int i=0;


    for(auto label:labels){
        int score = boxes.at(i)->itemText(i).toInt();
        score = userScores.getValueFromIndex(label)+score;
        QString scoreStr = QString("Total: %1").arg(score);
        totalScores.at(i)->setText(scoreStr);
        updatedScores.setFromIndex(label,score);
    }

}

