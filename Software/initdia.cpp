#include "initdia.h"
#include <QDebug>
#include <iostream>

InitDia::InitDia()
{
    getnum["0"] = 0;
    getnum["W1"] = 1;
    getnum["W2"] = 2;
    getnum["W3"] = 3;
    getnum["W4"] = 4;
    getnum["W5"] = 5;
    getnum["W6"] = 6;
    getnum["W7"] = 7;
    getnum["W8"] = 8;
    getnum["W9"] = 9;

}

int InitDia::ReadJson(QString addr,vector<vector<QString>>&Model)
{

    QFile file(addr);
    if(!file.open(QIODevice::ReadOnly))
    {
        return OPEN_FILE_ERROR;
    }
    QJsonParseError jerr;
    //QTextStream stream(&file);
    //QString str = stream.readAll();
    QByteArray allData = file.readAll();
    file.close();
    //QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(),&jerr);
    QJsonDocument doc = QJsonDocument::fromJson(allData,&jerr);
    //cout<<allData.toStdString();
    //cout<<0<<endl;
    if(doc.isNull())
        return ERROR_FILE;
    QJsonObject jroot = doc.object();
    //读取文本内容
    //cout<<1<<endl;
    if(jroot.contains("WidgeText")&&jroot["WidgeText"].isObject())
        WidgeText = jroot["WidgeText"].toObject();
    else
        return  FORMAT_ERROR;
    QJsonObject JP;
//cout<<2<<endl;
    if(jroot.contains("jump")&&jroot["jump"].isObject())
        JP = jroot["jump"].toObject();
    else
        return  FORMAT_ERROR;
    QJsonObject::Iterator it;
    for(it=JP.begin();it!=JP.end();it++)
    {
        map<QString,QString> a;
        QJsonObject nr = it.value().toObject();
        QJsonObject::Iterator iteratorJson;
        iteratorJson = nr.begin();
        while(iteratorJson != nr.end()){
            QString b = iteratorJson.value().toString();
            QString c = iteratorJson.key();
            a[c] = b;
            iteratorJson++;
        }
        WJump[it.key()] = a;
    }
//    cout<<3<<endl;
//    for(auto i:WJump)
//    {
//        cout<<i.first.toStdString()<<" :"<<endl;
//        for(auto j:i.second)
//        {
//            cout<<" "<<j.first.toStdString()<<" "<<j.second.toStdString()<<endl;
//        }
//    }
    QJsonObject lig;
    if(jroot.contains("logic")&&jroot["logic"].isObject())
        lig = jroot["logic"].toObject();
    else
        return  FORMAT_ERROR;
    for(it=lig.begin();it!=lig.end();it++)
    {
        QString name = it.key();
        int num = getnum[name];
        QJsonArray arr = it.value().toArray();
        int TSize = arr.size();
        for(int i=0;i<TSize;++i)
        {
            logic a;
            a.show = arr.at(i).toObject().value("show").toString();
            QJsonArray brr = arr.at(i).toObject().value("seq").toArray();
            int BSize = brr.size();
            for(int j=0;j<BSize;++j)
                a.seq.push_back(brr.at(j).toString());
            lc[num].push_back(a);
        }
    }

    QJsonArray Md;
    if(jroot.contains("model")&&jroot["model"].isArray())
    {
        Md = jroot["model"].toArray();
        for(auto i:Md)
        {
            QJsonArray j = i.toArray();
            cout<<" "<<j.size()<<endl;
            vector<QString> vec;
            for(auto k:j)
                vec.push_back(k.toString());
            Model.push_back(vec);
        }
    }
    else
        return  FORMAT_ERROR;


//    for(int i=0;i<10;++i)
//    {
//        cout<<i<<" "<<endl;
//        for(auto j:lc[i])
//        {
//            for(auto k:j.seq)
//                cout<<k.toStdString()<<" ";
//            cout<<endl;
//            cout<<j.show.toStdString()<<endl;
//        }
//    }
    return 0;
}

bool InitDia::JudgeExist(QString w, QString id,QJsonObject &ct)
{
    if(WidgeText.contains(w) && WidgeText[w].isObject())
    {
        ct = WidgeText[w].toObject();
    }
    else
        return 0;
    if(ct.contains(id) && ct[id].isObject())
    {
        ct = ct[id].toObject();
    }
    else
        return 0;
    return 1;
}

QString InitDia::nxt(QString name,vector<QString> seq)
{
    int num = getnum[name];
   // cout<<"nxt:"<<name.toStdString()<<" "<<num<<" "<<lc[num].size()<<endl;
    for(int i=0;i<lc[num].size();++i)
    {
        int l = lc[num][i].seq.size();
        cout<<l<<endl;
        bool ok = 1;
        if(seq.size()<l)
            continue;
        for(int j = 0;j<l && ok;++j)
            if(seq[seq.size()-1-j]!=lc[num][i].seq[l-1-j])
                ok=0;
        if(ok)
            return lc[num][i].show;
    }
    return "NaN";
}

QString InitDia::nJump(QString now, QString para)
{
    //cout<<now.toStdString()<<" "<<para.toStdString()<<" "<<WJump[now][para].toStdString()<<endl;
    return WJump[now][para];
}

bool InitDia::GetContent(QString name, vector<pair<QString,vector<QString>>> &ret, QJsonObject ct)
{
    if(ct[name].isString())
    {
        vector<QString> a;
        a.push_back(ct[name].toString());
        ret.push_back(make_pair(name,a));
        return 1;
    }
    else if(ct[name].isArray())
    {
        QJsonObject::Iterator it;
        vector<QString> a;
        QJsonArray arr = ct[name].toArray();
        int TSize = arr.size();
        for(int i=0;i<TSize;++i)
        {
            QString nr = arr.at(i).toString();
            a.push_back(nr);
        }
        ret.push_back(make_pair(name,a));
        return 1;
    }
    return 0;
}

vector<pair<QString,vector<QString>>> InitDia::ReadW(QString wn, QString id)
{
    int cc;
    QJsonObject ct;
    //qDebug()<<"110:"<<wn<<" "<<id;
    cc = JudgeExist(wn,id,ct);
    vector<pair<QString,vector<QString>>> ret;
    //cout<<cc<<":1111"<<endl<<endl;;
    if(!cc)
        return ret;
   // cout<<"111"<<endl;
    QJsonObject::Iterator it;
    for(it=ct.begin();it!=ct.end();it++)
        GetContent(it.key(),ret,ct);
    return ret;
}
map<QString,QString> InitDia::GetJump(QString name)
{
    return WJump[name];
}
