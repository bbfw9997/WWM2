#ifndef DISPLAYMESSAGEBOX_H
#define DISPLAYMESSAGEBOX_H

#include <QWidget>

class DisplayMessageBox
{

public:
    DisplayMessageBox();
    DisplayMessageBox(QWidget *parent, QString message);
    ~DisplayMessageBox();
};

#endif // DISPLAYMESSAGEBOX_H
