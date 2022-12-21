#ifndef MODELRUN_H
#define MODELRUN_H
#include<initdia.h>
#include<vector>
#include<iostream>
using namespace std;

struct RET
{
    QString Dia;

    vector<pair<QString,vector<QString>>> dd;

};


class ModelRun
{
public:
    ModelRun();
    ModelRun(QString addr);
    RET NextStep(QString parm,QString show);
    void init(QString addr);
    vector<RET> all(QString name);
    QString undo();
    vector<QString> GetModel(int idx);
    map<QString,QString> GetJump(QString name);
private:
    QString now;
    InitDia Core;
    vector<QString> seq;
    vector<vector<QString>> Model;
};

#endif // MODELRUN_H
