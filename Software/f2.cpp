#include "f2.h"
#include "ui_f2.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QButtonGroup>
#include<iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QFont>
#include <QTextCodec>
using namespace std;
f2::f2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::f2)
{
    //

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->W2S->setWordWrap(true);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    ui->pics->setAlignment(Qt::AlignCenter);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    timer->start(10000);
    on_timer();

    qDebug()<<ui->C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C1->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C2->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C3->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C4->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C5->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C5->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C6->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C6->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C7->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C7->mapToGlobal(QPoint(0,0)).y();
    qDebug()<<ui->C8->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->C8->mapToGlobal(QPoint(0,0)).y();
}

f2::~f2()
{
    delete ui;
}

void f2::on_timer()
{
    if (picList.count() == 0)
    {
        return;
    }
    static int cnt = 0;
    picture = QPixmap(picList[cnt]);
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    cnt++;
    if (cnt >= picList.count())
        cnt = 0;
    timer->start(10000);
}

void f2::on_C1_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C2_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C3_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C4_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C5_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C6_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C7_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
void f2::on_C8_clicked()
{
    //picture = picture.scaled(ui->pics->size(),Qt::KeepAspectRatio);
    ui->pics->setPixmap(picture);
    timer->start(10000);
}
