#ifndef INITDIA_H
#define INITDIA_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include<string>
#include <QFile>
#include <map>
#include <iostream>
#define OPEN_FILE_ERROR 1
#define ERROR_FILE 2
#define FORMAT_ERROR 3
using namespace std;

struct jsonInfo
{
    int t;
    QString h;
    bool f;
};

struct logic
{
    vector<QString> seq;
    QString show;
    long long hx1;
    long long hx2;
};

class InitDia
{
private:
    bool JudgeExist(QString w,QString id,QJsonObject &ct);
    QJsonObject WidgeText;
    map<QString,map<QString,QString>> WJump;
    vector<logic> lc[20];
    map<QString,int> getnum;
    bool GetContent(QString name,vector<pair<QString,vector<QString>>> &ret,QJsonObject ct);

public:
    InitDia();
    int ReadJson(QString addr,vector<vector<QString>>&Model);
    vector<pair<QString,vector<QString>>> ReadW(QString w,QString id);
    //int ReadJson(std::string addr);
    QString nxt(QString name, vector<QString> seq);
    QString nJump(QString now,QString para);
    map<QString,QString> GetJump(QString name);
};

#endif // INITDIA_H
