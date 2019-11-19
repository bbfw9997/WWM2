#include "gamelogic.h"
#include "messagebox.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <chrono>
#include <ctime>



GameLogic::GameLogic(){}

void GameLogic::loadFile(QWidget *parent, QString filePath){
    file.setFileName(filePath);
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        MessageBox msgBox;
        msgBox.displayMessageBox(parent, "Error", "Couldn't open File or file does not exist!", 1);
    }

    QTextStream in(&file);
    QList<int> boundariesList;
    boundariesList.clear();
    int counter = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line == "[L]"){
            boundariesList.append(counter);
        } else if(line == "[M]"){
            boundariesList.append(counter);
        } else if (line == "[H]"){
            boundariesList.append(counter);
        } else if(line == "[E]"){
            boundariesList.append(counter);
        }
        counter++;
    }

    file.close();

    startToEnd.clear();
    std::srand(time(0));
    QList<int> container;
    for(counter = 1; counter <= boundariesList.last(); counter++){
        if(counter == boundariesList[1]){
        } else if(counter == boundariesList[2]) {
        } else if(counter == boundariesList[3]){
        } else {
            container.append(counter);
        }

        if(counter == boundariesList[1] || counter == boundariesList[2] || counter == boundariesList[3]){
            std::random_shuffle(container.begin(), container.end());
            if(container.size() > 5){
                container.erase(container.begin()+5, container.end());
            }
            startToEnd.append(container);
            container.clear();
        }

        qDebug () << "startToEnd :: " << startToEnd;
    }
}


QString GameLogic::nextQuestion(int index){
    int lineCounter = 0;
    QString line;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        line = in.readLine();
        if(lineCounter == startToEnd[index]){
            file.close();
            return line;
        }
        else {
            lineCounter++;
            continue;
        }
    }
    file.close();
    return "";
}

QList<int> GameLogic::getIndexes(){
    return startToEnd;
}



