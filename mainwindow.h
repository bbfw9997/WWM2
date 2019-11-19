#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "messagebox.h"
#include <QPushButton>
#include "gamelogic.h"
#include <QListWidgetItem>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialization();
    QList<QString> RegExSplit(QString line);
    //QPushButton *uiElements[5];
    int questionCounter;
    QString answer;
    QString rightAnswer;
    QButtonGroup* buttonGroup;
    void populateElements(QList<QString> spLine);
    void changeBgColor(int);
    void resetButtonsColor();
    void CallNextQuestion();
    GameLogic gameLogic;
    void RightAfterInit();
    bool isGreen = false;
    void ResetAll();

private slots:
    void on_buttonGroup_buttonReleased(int);
    void on_bu_checkanswer_released();
    void on_list_amount_itemClicked(QListWidgetItem *item);
    void animBlinkingButtonRight();
    void resetListItemAmount();

    void on_bu_aufgeben_released();

    void on_bu_start_released();

    void on_bu_exit_released();

private:
    QTimer *timer;
    QTimer *timerBlinking;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
