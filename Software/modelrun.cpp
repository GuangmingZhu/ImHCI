#include "modelrun.h"

ModelRun::ModelRun()
{
    now = "W1";
    seq.push_back(now);
}

ModelRun::ModelRun(QString addr)
{

}

void ModelRun::init(QString addr)
{
    Core.ReadJson(addr,Model);
}

RET ModelRun::NextStep(QString parm, QString show)
{
//    QString nxt = Core.nJump(now,parm);
//    cout<<"1"<<now.toStdString()<<" "<<nxt.toStdString()<<endl;
//    auto a = Core.nxt(nxt,seq);
//    RET ret;
//    auto b = Core.ReadW(nxt,show);
//    cout<<"1:"<<now.toStdString()<<" "<<nxt.toStdString()<<" "<<parm.toStdString()<<endl;
//    now = nxt;
//    ret.Dia = now;
//    ret.dd = b;
//    seq.push_back(now);

    QString nxt = parm;
    RET ret;
    auto b = Core.ReadW(parm,show);
    ret.Dia = parm;
    ret.dd = b;
    seq.push_back(parm);
    return ret;
}
vector<RET> ModelRun::all(QString name)
{
    vector<RET> ret;

    RET a;
    auto w1 = Core.ReadW("W5",name);
    a.Dia = "W5";
    a.dd = w1;
    ret.push_back(a);

    w1 = Core.ReadW("W6",name);
    a.Dia = "W6";
    a.dd = w1;
    ret.push_back(a);

    w1 = Core.ReadW("W7",name);
    a.Dia = "W7";
    a.dd = w1;
    ret.push_back(a);

    w1 = Core.ReadW("W8",name);
    a.Dia = "W8";
    a.dd = w1;
    ret.push_back(a);

    w1 = Core.ReadW("W9",name);
    a.Dia = "W9";
    a.dd = w1;
    ret.push_back(a);

    return ret;
}

QString ModelRun::undo()
{
    if(seq.size()<=2)
        return "NaN";
    seq.pop_back();
    now = seq[seq.size()-1];
    return seq[seq.size()-1];
}

vector<QString> ModelRun::GetModel(int idx)
{
    if(idx>Model.size())
        return vector<QString>();
    return Model[idx-1];
}

map<QString,QString> ModelRun::GetJump(QString name)
{
    return Core.GetJump(name);
}
