#include "messagebox.h"
#include <QMessageBox>
#include <QWidget>


MessageBox::MessageBox(){}

void MessageBox::displayMessageBox(QWidget *parent, QString title, QString message, qint16 type){
    switch (type) {
    case 0:
        QMessageBox::information(parent, title, message);
        break;
    case 1:
        QMessageBox::critical(parent, title, message);
        break;
    case 2:
        QMessageBox::warning(parent, title, message);
    }
}
