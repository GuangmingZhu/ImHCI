#ifndef GETMSG_H
#define GETMSG_H
#include<QThread>
#include<vector>
#include<QMutex>
using namespace std;
struct data{
    QString times;
    QString gazeX;
    QString gazeY;
    QString mouseX;
    QString mouseY;
    QString pd;
};

class Getmsg:public QThread
{
    Q_OBJECT
public:
    Getmsg();
    void setprop(QString a,QString b,QString c);
    virtual void run();
public slots:
    void StopThread();
    void start1();

private:
    bool is_stop_;
    int count_;
    QString addr;
    QString name;
    QString starttime;
    QString endtime;
    QString date;
    vector<data> vec;
    QMutex m_mutex;
};

#endif // GETMSG_H
