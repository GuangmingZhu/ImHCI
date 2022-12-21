#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    //setWindowFlag(Qt::FramelessWindowHint);
//    setWindowFlags(Qt::FramelessWindowHint);
//    isStart = false;     //初始为还未计时
//    isClick = 1;
//    timer = new QTimer;
//    timer1 = new QTimer;
//    m_secCnt = 54;
//    m_minCnt = 24;
//    //ui->label->setStyleSheet("color:white");
//    //ui->label->setStyleSheet("font-size:40px;color:white");
//    //w.TS();
//    //init();
//    connect(timer,SIGNAL(timeout()),this,SLOT(ST()));
//    connect(timer1,SIGNAL(timeout()),this,SLOT(ST1()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::TS()
{
    //if(!isStart) //尚未开始 开始计时
    {
        m_secCnt = 54;
        m_minCnt = 24;
        timer->start(1000);
        ui->D4T->setText("00:05");
        isStart = 1;
        isClick = 0;
    }
}
void MainWindow::TS1()
{
    //if(!isStart) //尚未开始 开始计时
    {
        m_secCnt = 54;
        m_minCnt = 24;
        timer1->start(1000);
        ui->D5T->setText("00:05");
        isStart = 1;
        isClick = 0;
    }
}
void MainWindow::ST()
{
    m_secCnt++;
   if(m_secCnt >= 60) {
       m_secCnt = 0;
       m_minCnt++;
   }
   if(m_minCnt >= 25) {
       //disconnect(timer,SIGNAL(timeout()),this,SLOT(updateTime200()));
       timer->stop();
       m_secCnt = 0;
       m_minCnt = 0;
       isStart = false;
   }
   QString min = QString::number(24 - m_minCnt);
   QString sec = QString::number(59 - m_secCnt);
   if(min=="0" && sec =="0")
       isClick = 1;
   if(min.length() == 1) min = "0" + min;
   if(sec.length() == 1) sec = "0" + sec;
   QString timeToShow = min + ":" + sec;

   if(isStart)
        ui->D4T->setText(timeToShow);
}
void MainWindow::ST1()
{
    m_secCnt++;
   if(m_secCnt >= 60) {
       m_secCnt = 0;
       m_minCnt++;
   }
   if(m_minCnt >= 25) {
       //disconnect(timer,SIGNAL(timeout()),this,SLOT(updateTime200()));
       timer1->stop();
       m_secCnt = 0;
       m_minCnt = 0;
       isStart = false;
   }
   QString min = QString::number(24 - m_minCnt);
   QString sec = QString::number(59 - m_secCnt);
   if(min=="0" && sec =="0")
       isClick = 1;
   if(min.length() == 1) min = "0" + min;
   if(sec.length() == 1) sec = "0" + sec;
   QString timeToShow = min + ":" + sec;

   if(isStart)
        ui->D5T->setText(timeToShow);
}
void MainWindow::updateText(int idx,QString ct)
{
    std::cout<<idx<<" "<<ct.toStdString()<<std::endl;
    if(idx==1)
    {
        ui->D1S->setText(ct);
    }else if(idx==2)
    {
        ui->D2S->setText(ct);
    }else if(idx==3)
    {
        ui->D3S->setText(ct);
    }
}

void MainWindow::update(QString idx)
{
    if(idx!=NowStep.click || !isClick)
        return;
    if(NowStep.Dia[0]=="D")
        NowDia->hide();
    else{

    }
    for(auto i:NowSee)
        i->hide();
    NowDia = 0;
    NowButton = 0;
    NowSee.clear();
    NowStep = MR.NextStep();
    if(NowStep.Dia[0]=="D")
    {
        NowDia = findQw(NowStep.Dia);
        //NowDia->show();
        if(NowStep.Dia=="D1")
            D1(1,1,1);
        else if(NowStep.Dia=="D2")
            D2(1,1,1);
        else if(NowStep.Dia=="D3")
            D3(1,1,1);
        else if(NowStep.Dia=="D4")
            D4(1,1,1);
        else if(NowStep.Dia=="D5")
            D5(1,1,1);
        else if(NowStep.Dia=="D6")
            D6(1,1,1);
        else if(NowStep.Dia=="D7")
            D7(1,1,1);
        else if(NowStep.Dia=="D8")
            D8(1,1,1);
    }
    else
    {
        NowButton = findB(NowStep.Dia);

    }
    cout<<2<<endl;
    for(int i=0;i<NowStep.see.size();++i)
    {
        auto j = findQw(NowStep.see[i]);
        NowSee.push_back(j);
        j->show();
        findQTB(NowStep.see[i])->setText(NowStep.content[i]);
        if(NowStep.see[i]=="D1")
            D1(1,1,0);
        else if(NowStep.see[i]=="D2")
            D2(1,1,0);
        else if(NowStep.see[i]=="D3")
            D3(1,1,0);
        else if(NowStep.see[i]=="D4")
            D4(1,1,1);
        else if(NowStep.see[i]=="D5")
            D5(1,1,1);
        else if(NowStep.see[i]=="D6")
            D6(1,1,0);
        else if(NowStep.see[i]=="D7")
            D7(1,1,0);
        else if(NowStep.see[i]=="D8")
            D8(1,1,0);
        if(NowStep.see[i]=="D4")
            TS();
        if(NowStep.see[i]=="D5")
            TS1();
    }
    cout<<3<<endl;
    cout<<NowStep.see.size()<<" "<<NowStep.Dia.toStdString()<<endl;
    if(NowStep.Dia[0]=="D")
    {
        findQTB(NowStep.Dia)->setText(NowStep.content[NowStep.see.size()]);
    }
    cout<<4<<endl;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::dialoginit()
{
    ui->mainToolBar->hide();
    ui->menuBar->hide();
    ui->statusBar->hide();

    //第一个窗口
    ui->D1B1->resize(70,40);
    ui->D1B1->move(70,210);
    ui->D1B2->resize(70,40);
    ui->D1B2->move(170,210);
    ui->D1B3->resize(70,40);
    ui->D1B3->move(270,210);
    ui->D1S->resize(370,120);
    ui->D1S->move(60,70);
    ui->D1B1->setText("A");
    ui->D1B2->setText("B");
    ui->D1B3->setText("C");

    //第二个窗口
    ui->D2B1->resize(70,40);
    ui->D2B1->move(70,210);
    ui->D2B2->resize(70,40);
    ui->D2B2->move(170,210);
    ui->D2B3->resize(70,40);
    ui->D2B3->move(270,210);
    ui->D2S->resize(370,120);
    ui->D2S->move(60,70);
    ui->D2B1->setText("A");
    ui->D2B2->setText("B");
    ui->D2B3->setText("C");

    //第三个窗口
    ui->D3B1->resize(70,40);
    ui->D3B1->move(70,210);
    ui->D3B2->resize(70,40);
    ui->D3B2->move(170,210);
    ui->D3B3->resize(70,40);
    ui->D3B3->move(270,210);
    ui->D3S->resize(370,120);
    ui->D3S->move(60,70);
    ui->D3B1->setText("A");
    ui->D3B2->setText("B");
    ui->D3B3->setText("C");

    //第六个窗口
    ui->D6B1->resize(70,40);
    ui->D6B1->move(70,210);
    ui->D6B2->resize(70,40);
    ui->D6B2->move(170,210);
    ui->D6B3->resize(70,40);
    ui->D6B3->move(270,210);
    ui->D6S->resize(370,120);
    ui->D6S->move(60,70);
    ui->D6B1->setText("A");
    ui->D6B2->setText("B");
    ui->D6B3->setText("C");

    //第七个窗口
    ui->D7B1->resize(70,40);
    ui->D7B1->move(70,210);
    ui->D7B2->resize(70,40);
    ui->D7B2->move(170,210);
    ui->D7B3->resize(70,40);
    ui->D7B3->move(270,210);
    ui->D7S->resize(370,120);
    ui->D7S->move(60,70);
    ui->D7B1->setText("A");
    ui->D7B2->setText("B");
    ui->D7B3->setText("C");

    //第八个窗口
    ui->D8B1->resize(70,40);
    ui->D8B1->move(70,210);
    ui->D8B2->resize(70,40);
    ui->D8B2->move(170,210);
    ui->D8B3->resize(70,40);
    ui->D8B3->move(270,210);
    ui->D8S->resize(370,120);
    ui->D8S->move(60,70);
    ui->D8B1->setText("A");
    ui->D8B2->setText("B");
    ui->D8B3->setText("C");

    ui->D1->hide();
    ui->D2->hide();
    ui->D3->hide();
    ui->D4->hide();
    ui->D5->hide();
    ui->D6->hide();
    ui->D7->hide();
    ui->D8->hide();


}

void MainWindow::init()
{
    dialoginit();
    MR.init("./prop.json");
    NowStep = MR.NextStep();
    if(NowStep.Dia[0]=="D")
    {
        NowDia = findQw(NowStep.Dia);
        //NowDia->show();
        if(NowStep.Dia=="D1")
            D1(1,1,1);
        else if(NowStep.Dia=="D2")
            D2(1,1,1);
        else if(NowStep.Dia=="D3")
            D3(1,1,1);
        else if(NowStep.Dia=="D4")
            D4(1,1,1);
        else if(NowStep.Dia=="D5")
            D5(1,1,1);
        else if(NowStep.Dia=="D6")
            D6(1,1,1);
        else if(NowStep.Dia=="D7")
            D7(1,1,1);
        else if(NowStep.Dia=="D8")
            D8(1,1,1);
    }
    else
    {
        NowButton = findB(NowStep.Dia);

    }
    for(int i=0;i<NowStep.see.size();++i)
    {
        auto j = findQw(NowStep.see[i]);
        NowSee.push_back(j);
        j->show();
        findQTB(NowStep.see[i])->setText(NowStep.content[i]);
        if(NowStep.see[i]=="D1")
            D1(1,1,0);
        else if(NowStep.see[i]=="D2")
            D2(1,1,0);
        else if(NowStep.see[i]=="D3")
            D3(1,1,0);
        else if(NowStep.see[i]=="D4")
            D4(1,1,0);
        else if(NowStep.see[i]=="D5")
            D5(1,1,0);
        else if(NowStep.see[i]=="D6")
            D6(1,1,0);
        else if(NowStep.see[i]=="D7")
            D7(1,1,0);
        else if(NowStep.see[i]=="D8")
            D8(1,1,0);
    }
    //cout<<3<<endl;
    if(NowStep.Dia[0]=="D")
    {
        findQTB(NowStep.Dia)->setText(NowStep.content[NowStep.see.size()]);
    }
    //cout<<4<<endl;
}
QPushButton* MainWindow::findB(QString name)
{
    return nullptr;
}

QWidget* MainWindow::findQw(QString name)
{
    if(name=="D1")
        return ui->D1;
    else if(name=="D2")
        return ui->D2;
    else if(name=="D3")
        return ui->D3;
    else if(name=="D4")
        return ui->D4;
    else if(name=="D5")
        return ui->D5;
    else if(name=="D6")
        return ui->D6;
    else if(name=="D7")
        return ui->D7;
}

QTextBrowser* MainWindow::findQTB(QString name)
{
    if(name=="D1")
        return ui->D1S;
    else if(name=="D2")
        return ui->D2S;
    else if(name=="D3")
        return ui->D3S;
    else if(name=="D4")
        return ui->D4S;
    else if(name=="D5")
        return ui->D5S;
    else if(name=="D6")
        return ui->D6S;
    else if(name=="D7")
        return ui->D7S;
}

void MainWindow::on_D1B2_clicked()
{
    update("B");
}

void MainWindow::on_D2B3_clicked()
{
    update("C");
}

void MainWindow::on_B2_clicked()
{
    update("B2");
}

void MainWindow::on_D7B3_clicked()
{
    update("C");
}

void MainWindow::on_B3_clicked()
{
    update("B3");
}

void MainWindow::on_B4_clicked()
{
    update("B4");
}

void MainWindow::on_D3B1_clicked()
{
    update("A");
}

void MainWindow::D1(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D1->show();
    else
        ui->D1->hide();
    if(Tv)
        ui->D1S->show();
    else
        ui->D1S->hide();
    if(Bv){
        ui->D1B1->show();
        ui->D1B2->show();
        ui->D1B3->show();
    }
    else{
        ui->D1B1->hide();
        ui->D1B2->hide();
        ui->D1B3->hide();
    }
}
void MainWindow::D2(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D2->show();
    else
        ui->D2->hide();
    if(Tv)
        ui->D2S->show();
    else
        ui->D2S->hide();
    if(Bv){
        ui->D2B1->show();
        ui->D2B2->show();
        ui->D2B3->show();
    }
    else{
        ui->D2B1->hide();
        ui->D2B2->hide();
        ui->D2B3->hide();
    }
}
void MainWindow::D3(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D3->show();
    else
        ui->D3->hide();
    if(Tv)
        ui->D3S->show();
    else
        ui->D3S->hide();
    if(Bv){
        ui->D3B1->show();
        ui->D3B2->show();
        ui->D3B3->show();
    }
    else{
        ui->D3B1->hide();
        ui->D3B2->hide();
        ui->D3B3->hide();
    }
}
void MainWindow::D4(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D4->show();
    else
        ui->D4->hide();
    if(Tv)
        ui->D4S->show();
    else
        ui->D4S->hide();
    if(Bv)
        ui->D4T->show();
    else
        ui->D4T->hide();
}
void MainWindow::D5(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D5->show();
    else
        ui->D5->hide();
    if(Tv)
        ui->D5S->show();
    else
        ui->D5S->hide();
    if(Bv)
        ui->D5T->show();
    else
        ui->D5T->hide();
}
void MainWindow::D6(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D6->show();
    else
        ui->D6->hide();
    if(Tv)
        ui->D6S->show();
    else
        ui->D6S->hide();
    if(Bv){
        ui->D6B1->show();
        ui->D6B2->show();
        ui->D6B3->show();
    }
    else{
        ui->D6B1->hide();
        ui->D6B2->hide();
        ui->D6B3->hide();
    }
}
void MainWindow::D7(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D7->show();
    else
        ui->D7->hide();
    if(Tv)
        ui->D7S->show();
    else
        ui->D7S->hide();
    if(Bv){
        ui->D7B1->show();
        ui->D7B2->show();
        ui->D7B3->show();
    }
    else{
        ui->D7B1->hide();
        ui->D7B2->hide();
        ui->D7B3->hide();
    }
}
void MainWindow::D8(bool vi, bool Tv, bool Bv)
{
    if(vi)
        ui->D8->show();
    else
        ui->D8->hide();
    if(Tv)
        ui->D8S->show();
    else
        ui->D8S->hide();
    if(Bv){
        ui->D8B1->show();
        ui->D8B2->show();
        ui->D8B3->show();
    }
    else{
        ui->D8B1->hide();
        ui->D8B2->hide();
        ui->D8B3->hide();
    }
}
void MainWindow::BU(bool vi)
{

}
*/
