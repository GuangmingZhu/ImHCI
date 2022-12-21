#include "getmsg.h"
#include<ctime>
#include<QFile>
#include<QTextStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include<qDebug>
using namespace std;

Getmsg::Getmsg()
{
    is_stop_ = true;
    count_ = 0;
    this->start();
}

void Getmsg::StopThread()
{
    cout<<1<<endl;
    time_t now = time(0);
    tm *ltm=localtime(&now);
    is_stop_ = true;
    QString h = QString::number(ltm->tm_hour);
    if(h.length()==1)
        h = "0"+h;
    QString m = QString::number(ltm->tm_min);
    if(m.length()==1)
        m = "0"+m;
    QString s = QString::number(ltm->tm_sec);
    if(s.length()==1)
        s = "0"+s;
    endtime = h+m+s;
    addr = "./data/"+addr + "-" +date+"-"+starttime+"-"+endtime+".csv";
    QFile file(addr);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream txtOutPut(&file);
    for(auto i:vec)
    {
        txtOutPut<<i.times<<","+i.gazeX<<","<<i.gazeY<<","<<i.mouseX<<","<<i.mouseY<<","<<i.pd<<"\n";
        file.flush();
    }
    file.close();
    cout<<2<<endl;
}
void Getmsg::start1()
{
    is_stop_ = false;
    time_t now = time(0);
    tm *ltm=localtime(&now);
    QString month = QString::number(ltm->tm_mon+1);
    if(month.length()==1)
        month = "0"+month;
    QString day = QString::number(ltm->tm_mday);
    if(day.length()==1)
        day = "0"+day;
    date = month+day;
    QString h = QString::number(ltm->tm_hour);
    if(h.length()==1)
        h = "0"+h;
    QString m = QString::number(ltm->tm_min);
    if(m.length()==1)
        m = "0"+m;
    QString s = QString::number(ltm->tm_sec);
    if(s.length()==1)
        s = "0"+s;
    starttime = h+m+s;
    vec.clear();
//    data a;
//    a.times = "0";
//    a.pd = "1";
//    a.gazeX = "2";
//    a.gazeY = "3";
//    a.mouseX = "4";
//    a.mouseY = "5";
//    vec.push_back(a);
}
void Getmsg::run()
{
    //cout<<114514<<endl;
    void *context = zmq_ctx_new();
    void *sub = zmq_socket(context,ZMQ_SUB);
    int rz = zmq_connect(sub,"tcp://localhost:5566");
    const char *filter = "";
    zmq_setsockopt(sub,ZMQ_SUBSCRIBE,filter,strlen(filter));
    while(1)
    {
        qDebug()<<1;
        while (!is_stop_) {
            char buffer[512];
            int size = zmq_recv(sub,buffer,512,0);
            //cout<<"11:"<<size<<endl;
            if(size!=-1)
            {
                buffer[size] = '\0';
                QString str(buffer);
                cout<<str.toStdString()<<endl;
                QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
                QJsonObject g = jdoc.object();
                data a;
                a.times = g.value("times").toString();
                cout<<a.times.toStdString()<<endl;
                a.gazeX = QString::number(g.value("gazeX").toInt());
                a.gazeY = QString::number(g.value("gazeY").toInt());
                a.mouseX = QString::number(g.value("mouseX").toInt());
                a.mouseY = QString::number(g.value("mouseY").toInt());
                a.pd = QString::number(g.value("pd").toInt());
                vec.push_back(a);
            }

        }
        sleep(1);
    }
}

void Getmsg::setprop(QString a, QString b, QString c)
{
    addr = a+b+c;
}
