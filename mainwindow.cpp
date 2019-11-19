#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagebox.h"
#include <QPixmap>
#include <QToolBar>
#include <QFile>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QSound>
#include "gamelogic.h"
#include <QButtonGroup>
#include <QPropertyAnimation>
#include "animation.h"
#include <windows.h>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::initialization();
    RightAfterInit();

}

void MainWindow::ResetAll(){
    questionCounter = 0;
    ui->container_qa->hide();
    ui->container_se->show();
    ui->bu_aufgeben->hide();
    RightAfterInit();
    for (int i = 0; i < 15;i++) {
        QString oldText = ui->list_amount->item(i)->text();
        if(oldText.contains("✦")){
            oldText.replace(" ✦ ","      ");
            ui->list_amount->item(i)->setText(oldText);
        }
    }

    ui->list_amount->setCurrentRow(14);
    resetButtonsColor();

}

void MainWindow::RightAfterInit(){
    QString filePath = ":/res/fragen.txt";
    gameLogic.loadFile(this, filePath);
    CallNextQuestion();
}

void MainWindow::CallNextQuestion(){
    int listSize = ui->list_amount->count() - 1;
    QString line = gameLogic.nextQuestion(questionCounter);
    QList<QString> splittedLine = RegExSplit(line);
    populateElements(splittedLine);
    ui->list_amount->setCurrentRow(listSize - questionCounter);
    questionCounter++;
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateElements(QList<QString> spLine){
    int i;
    for (i= 0; i <= 5; i++){
        switch (i){
        case 0:
            ui->txt_question->setText(spLine[i]);
            break;
        case 1:
            ui->bu_ans1->setText(spLine[i]);
            break;
        case 2:
            ui->bu_ans2->setText(spLine[i]);
            break;
        case 3:
            ui->bu_ans3->setText(spLine[i]);
            break;
        case 4:
            ui->bu_ans4->setText(spLine[i]);
            break;
        case 5:
            rightAnswer = spLine[i];
            break;
        }
    }
}

QList<QString> MainWindow::RegExSplit(QString line){
    QRegExp regex("([;]+)");
    QList<QString> splittedLine = line.split(regex);
    return  splittedLine;
}

//Initialisierung.
void MainWindow::initialization(){
    ui->setupUi(this);
    ui->statusBar->hide();
    ui->mainToolBar->hide();
    QPixmap pix;
    //Load background purple
    pix.load(":/res/backgroundimage_purple_black.jpg");
    ui->la_backgroundpicture->setPixmap(pix);

    //load Background blue
    ui->list_amount->setStyleSheet("background-image: url(:/res/background_liste_win.jpg)");

    // load Logo
    pix.load(":/res/wwm_logo.png");
    ui->label_logo->setPixmap(pix.scaled(300, 300, Qt::KeepAspectRatio));

    ui->txt_question->setStyleSheet("background-color: white");

    ui->container_qa->hide();
    ui->bu_aufgeben->hide();

    questionCounter = 0;

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->bu_ans1, 1);
    buttonGroup->addButton(ui->bu_ans2, 2);
    buttonGroup->addButton(ui->bu_ans3, 3);
    buttonGroup->addButton(ui->bu_ans4, 4);

    connect(buttonGroup, SIGNAL(buttonReleased(int)), this, SLOT(on_buttonGroup_buttonReleased(int)));
    //ui->container_qa->hide();

    connect(ui->list_amount, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_list_amount_itemClicked(QListWidgetItem*)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(resetListItemAmount()));

}

// Alle AntwortButtons.
void MainWindow::on_buttonGroup_buttonReleased(int id){
    for(int i = 1; i <= buttonGroup->buttons().count(); i++){
        if(id == i){
            answer = buttonGroup->button(i)->text();
            changeBgColor(id);
        }
    }
    ui->bu_checkanswer->setEnabled(true);
}

// Alle Schaltflächen auf graue Farbe.
void MainWindow::resetButtonsColor(){
    for(int i = 1; i <= buttonGroup->buttons().count(); i++){
       buttonGroup->button(i)->setStyleSheet("background-color: rgb(225,225,225)");
    }
}


// Farbe der Schaltflächen ändern
void MainWindow::changeBgColor(int id){
        for(int i = 1; i <= buttonGroup->buttons().count(); i++){
            if(id == i){
                buttonGroup->button(i)->setStyleSheet("background-color: rgb(230,230,0)");
            }
            else {
                buttonGroup->button(i)->setStyleSheet("background-color: rgb(225,225,225)");
            }
        }
}

// Button: check Answer
void MainWindow::on_bu_checkanswer_released()
{
    //MessageBox msgBox;
    //animation anim;

    int position = ui->list_amount->count()+1;
    qDebug() << "position::: " << questionCounter;
    if(answer == rightAnswer){
        //msgBox.displayMessageBox(this, "Info", "Die Antwort war richtig");
        ui->bu_checkanswer->setEnabled(false);
        animBlinkingButtonRight();
        resetButtonsColor();
        if(questionCounter == 15){
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben die €1Mio gewonnen! Gratulation!");
            ResetAll();
        }
        else {
        CallNextQuestion();
        }
        QString oldText = ui->list_amount->item(position-questionCounter)->text();
        oldText.replace("      ", " ✦ ");
        ui->list_amount->item(position-questionCounter)->setText(oldText);
    }
    else {

        QString amount;
        if(questionCounter < 5){
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben nichts gewonnen. Vielleicht gewinnen Sie beim nächsten Mal.");
        } else if(questionCounter >= 5 && questionCounter < 10){
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben €1000 gewonnen. Versuchen Sie es nochmal, vielleicht gewinnen Sie mehr");
        } else if(questionCounter >= 10){
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben €320000 gewonnen. Versuchen Sie es nochmal, vielleicht werden sie Millionär.");
        }

        ResetAll();

    }
}

void MainWindow::resetListItemAmount(){
    int position = ui->list_amount->count();
    ui->list_amount->setCurrentRow( position - questionCounter);

}

void MainWindow::on_list_amount_itemClicked(QListWidgetItem *item)
{
    timer->start(500);
}

void MainWindow::animBlinkingButtonRight(){
}



void MainWindow::on_bu_aufgeben_released()
{
    int position = ui->list_amount->count()+1;
    QMessageBox::StandardButton antwort;
    antwort = QMessageBox::question(this, "Aufgeben", "Wollen Sie wirklich aufgeben?", QMessageBox::Yes|QMessageBox::No);
    if(antwort == QMessageBox::Yes){
        if(questionCounter > 1){
            qint32 euroSignIndex = ui->list_amount->item(position - questionCounter)->text().indexOf("€");
            qDebug () << "euro :: " << euroSignIndex;
            QString amount = ui->list_amount->item(position - questionCounter)->text().mid(euroSignIndex);
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben " + amount + " gewonnen");
            ResetAll();


        } else {
            QMessageBox::information(this, "Herzlichen Glückwunsch", "Sie haben nichts gewonnen. Vielleicht gewinnen Sie beim nächsten Mal.");
            ResetAll();
        }
    } else {
        // mach nichts O_o
    }

}

void MainWindow::on_bu_start_released()
{
    ui->container_qa->show();
    ui->container_se->hide();
    ui->bu_aufgeben->show();

}

void MainWindow::on_bu_exit_released()
{
    QMessageBox::StandardButton antwort;
    antwort = QMessageBox::question(this, "Verlassen", "Wollen Sie wirklich das Spiel verlassen?", QMessageBox::Yes|QMessageBox::No);
    if(antwort == QMessageBox::Yes){
        QApplication::exit();
    }
}
