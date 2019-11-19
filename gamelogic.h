#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QString>
#include <QWidget>
#include <QFile>

class GameLogic
{
public:
    GameLogic();
    QList<int> startToEnd;
    void loadFile(QWidget *parent, QString filePath);
    QList<int> getIndexes();
    QString nextQuestion(int index);
    QFile file;
    
};

#endif // GAMELOGIC_H
