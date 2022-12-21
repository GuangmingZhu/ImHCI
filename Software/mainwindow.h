#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>
#include <modelrun.h>
#include<QPushButton>
#include<QTextBrowser>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void TS();
//    void TS1();
//    void updateText(int idx,QString ct);
//    void init();
private:
      Ui::MainWindow *ui;
//    QTimer *timer;
//    QTimer *timer1;
//    ModelRun MR;
//    int m_secCnt;
//    int m_minCnt;
//    bool isStart;
//    bool isClick;
//    void update(QString idx=0);
//    void dialoginit();
//    RET NowStep;
//    QWidget* findQw(QString name);
//    QTextBrowser* findQTB(QString name);
//    QPushButton* findB(QString name);
//    QWidget* NowDia;
//    QPushButton* NowButton;
//    vector<QWidget*>NowSee;

//    void D1(bool vi,bool Tv=1,bool Bv=1);
//    void D2(bool vi,bool Tv=1,bool Bv=1);
//    void D3(bool vi,bool Tv=1,bool Bv=1);
//    void D4(bool vi,bool Tv=1,bool Bv=1);
//    void D5(bool vi,bool Tv=1,bool Bv=1);
//    void D6(bool vi,bool Tv=1,bool Bv=1);
//    void D7(bool vi,bool Tv=1,bool Bv=1);
//    void D8(bool vi,bool Tv=1,bool Bv=1);
//    void BU(bool vi);
private slots:
//    void ST();
//    void ST1();
//    //ModelRun mR;
//    void on_pushButton_clicked();
//    void on_D1B2_clicked();
//    void on_D2B3_clicked();
//    void on_B2_clicked();
//    void on_D7B3_clicked();
//    void on_B3_clicked();
//    void on_B4_clicked();
//    void on_D3B1_clicked();
};

#endif // MAINWINDOW_H
