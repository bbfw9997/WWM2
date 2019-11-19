
#include <QWidget>

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H


class MessageBox
{
public:
    MessageBox();
    void displayMessageBox(QWidget *parent, QString title, QString message, qint16 type = 0);
};

#endif // MESSAGEBOX_H
