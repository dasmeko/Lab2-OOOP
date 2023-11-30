#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow()
{
    doNotLbl = new QLabel("Do not disturbe mode");
    doNotCheckBox = new QCheckBox();
    doNotCheckBox->setChecked(false);
    doNotDisturb = false;

    tmp = "\0";
    temp.setHMS(0,0,0);
    setToolBar();

    QLabel *tmr = new QLabel("Nearest Timer",this);
    tmr->setGeometry(50,85,100,20);
    mainTimerLbl = new QLabel(this);
    mainTimerLbl->setText("00:00:00");
    mainTimerLbl->setGeometry(40,100,130,40);

    QFont font = mainTimerLbl->font();
    font.setPixelSize(32);
    mainTimerLbl->setFont(font);

    QLabel *desc = new QLabel("Description",this);
    desc->setGeometry(260,60,70,20);

    mainTimerDescriptionLbl = new QTextEdit(this);
    mainTimerDescriptionLbl->setGeometry(250,80,230,100);
    mainTimerDescriptionLbl->setReadOnly(true);

    QLabel *tmrslbl = new QLabel("Timers",this);
    tmrslbl->setGeometry(40,205,50,20);

    QScrollBar *sb = new QScrollBar(Qt::Vertical);

    listW = new QListWidget(this);
    listW->setVerticalScrollBar(sb);
    listW->setGeometry(30,225,200,200);

    startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    timelbl->setText(QTime::currentTime().toString());
    if(timers.size() > 0){
        for(int i = 0; i < timers.size(); i++){
            timers[i].setTime(timers[i].getTime().addMSecs(-500));
            listW->item(i)->setText(timers[i].getTime().toString());
        }
        if(!stoppedTimersPositions.empty()){
            for(int i = 0; i < stoppedTimersPositions.size(); i++){
                timers[stoppedTimersPositions[i]].setTime(timers[stoppedTimersPositions[i]].getTime().addMSecs(500));
            }
        }
        mainTimerLbl->setText(timers[0].getTime().toString());
        mainTimerDescriptionLbl->setText(timers[0].getDesc());

        if(timers[0].getTime() == temp){
            timeoutWindow();
            timers.removeAt(0);
            delete listW->takeItem(0);
        }

        for(int i = 0; i < timers.size(); i++){
            if(timers[i].getTime() == temp){
                stoppedTimersPositions.append(i);
                timers.removeAt(i);
                delete listW->takeItem(i);
            }

        }

    } else {
        mainTimerDescriptionLbl->setText("\0");
    }
}

QList<Timer> MainWindow::getTimers()
{
    if(timers.size() > 0){
        for(int i = 0; i < timers.size(); i++){
            qDebug() << timers[i].getTime();
            qDebug() << timers[i].getDesc() << Qt::endl;
        }
        return timers;
    } else qDebug() << "No!" << Qt::endl;
}

void MainWindow::setToolBar()
{
    QPixmap addpix("add.png");
    QPixmap editpix("edit.png");
    QPixmap deletepix("delete.png");
    QPixmap deleteallpix("deleteAll.png");
    QPixmap infopix("info.png");
    QPixmap stoppix("stop.jpg");

    toolbar = addToolBar("Main Toolbar");
    toolbar->setFixedHeight(50);
    toolbar->setStyleSheet("QToolBar{spacing:10px;}");

    toolbar->addSeparator();
    QAction *add = toolbar->addAction(QIcon(addpix),"New Timer");
    QAction *stop = toolbar->addAction(QIcon(stoppix),"Stop timer");
    QAction *edit = toolbar->addAction(QIcon(editpix),"Edit Timer");
    QAction *dlete = toolbar->addAction(QIcon(deletepix),"Delete Timer");
    QAction *dleteAll = toolbar->addAction(QIcon(deleteallpix),"Delete All Timers");
    QAction *info = toolbar->addAction(QIcon(infopix),"Timer's Info");
    toolbar->setMovable(false);
    toolbar->addSeparator();

    QLabel *lbl = new QLabel("Current time: ");

    toolbar->addWidget(lbl);

    timelbl = new QLabel(QTime::currentTime().toString());
    startTimer(1000);
    toolbar->addWidget(timelbl);

    connect(stop, &QAction::triggered, this, &MainWindow::stopTimer);
    connect(add, &QAction::triggered, this, &MainWindow::addTimer);
    connect(edit, &QAction::triggered, this, &MainWindow::toEditWindow);
    connect(dlete, &QAction::triggered, this, &MainWindow::deleteTimer);
    connect(dleteAll, &QAction::triggered, this, &MainWindow::deleteAllTimers);
    connect(info, &QAction::triggered, this, &MainWindow::settingsWindowSlot);
}

