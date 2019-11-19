#include "animation.h"
#include <QPushButton>
#include <windows.h>
#include <QDebug>


animation::animation(){}

void animation::animBlinkingButtonRight(QAbstractButton *btn){
    bool isGreen = false;

    for (int i = 0; i < 5; i++) {
        if(isGreen){
            qDebug() << "nicht Grün";
            btn->setStyleSheet("background-color: rgb(225,225,225)");
            isGreen = false;
        } else {
            qDebug() << "Grün";
            btn->setStyleSheet("background-color: rgb(50,205,50)"); // green.
            isGreen = true;
        }

        Sleep(1000);
    }
}
