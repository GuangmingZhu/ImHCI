#include "f3.h"
#include "ui_f3.h"
#include<QDebug>
#include<QMovie>
#include<QDir>
f3::f3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::f3)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    MR.init("./prop.json");
    modeltype = 1;
    now_model = 0;
    Model = MR.GetModel(modeltype);
    QWidget::setTabOrder(ui->W9T1,ui->W9T2);
    QWidget::setTabOrder(ui->W9T2,ui->W9T3);
    QWidget::setTabOrder(ui->W9T3,ui->W9T4);
    type = "1";
    ui->W1C2->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C3->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C4->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C2->setDisabled(true);
    ui->W1C3->setDisabled(true);
    ui->W1C4->setDisabled(true);

    ui->W9L1->setWordWrap(true);
    ui->W9L2->setWordWrap(true);
    ui->W2S->setWordWrap(true);
    ui->W5S->setWordWrap(true);
    ui->W6S->setWordWrap(true);
    ui->W7S->setWordWrap(true);
    ui->W8S->setWordWrap(true);
    ui->W9S->setWordWrap(true);
    ui->W5L1->setAlignment(Qt::AlignRight);
    ui->W5L2->setAlignment(Qt::AlignRight);
    ui->W6L1->setAlignment(Qt::AlignRight);
    ui->W6L2->setAlignment(Qt::AlignRight);
    ui->W5L1->setAlignment(Qt::AlignRight);

    ui->W9L1->setAlignment(Qt::AlignRight);
    ui->W9L2->setAlignment(Qt::AlignRight);
    ui->W9L3->setAlignment(Qt::AlignRight);
    ui->W9L4->setAlignment(Qt::AlignRight);

    ui->W3S->hide();

    ui->W1C1->setSizeIncrement(90,40);
    ui->W1C2->setSizeIncrement(90,40);
    ui->W1C3->setSizeIncrement(90,40);
    ui->W1C4->setSizeIncrement(90,40);

    ui->W3S->setAlignment(Qt::AlignCenter);

    QFile file("./prop.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonParseError jerr;
        QByteArray allData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(allData,&jerr);
        QJsonObject jroot = doc.object();
        if(jroot.contains("picshow"))
        {
            QJsonObject picshow1=jroot["picshow"].toObject();
            QJsonObject::Iterator it;
            for(it=picshow1.begin();it!=picshow1.end();++it)
            {
                vector<QString> nm;
                QJsonArray arr = it.value().toArray();
                int TSize = arr.size();
                for(int i=0;i<TSize;++i)
                {
                    QString nr = arr.at(i).toString();
                    nm.push_back(nr);
                }
                picshow[it.key()] = nm;


            }
        }
    }
    file.close();
    initpt();
    timer = new QTimer(this);
    timer->start(10000);

    qDebug()<<"W1";
    qDebug()<<ui->W1C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W1C1->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W1C1->size();
    qDebug()<<ui->W1C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W1C2->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W1C2->size();
    qDebug()<<ui->W1C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W1C3->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W1C3->size();
    qDebug()<<ui->W1C4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W1C4->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W1C4->size();
    qDebug()<<"W2";
    qDebug()<<ui->W2C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W2C1->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W2C1->size();
    qDebug()<<ui->W2C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W2C2->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W2C2->size();
    qDebug()<<ui->W2C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W2C3->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W2C3->size();
    qDebug()<<ui->W2C4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W2C4->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W2C4->size();
    qDebug()<<ui->W2N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5N1->mapToGlobal(QPoint(0,0)).y()<<ui->W2N1->size();
    qDebug()<<ui->W2N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5N2->mapToGlobal(QPoint(0,0)).y()<<ui->W2N2->size();
    qDebug()<<"W3";
    qDebug()<<ui->pushButton_4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_4->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_4->size();
    qDebug()<<ui->pushButton_5->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_5->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_5->size();
    qDebug()<<ui->pushButton_6->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_6->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_6->size();
    qDebug()<<ui->pushButton_11->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_11->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_11->size();
    qDebug()<<"W5";
    qDebug()<<ui->W5T1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5T1->mapToGlobal(QPoint(0,0)).y()<<ui->W5T1->size();
    qDebug()<<ui->W5T2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5T2->mapToGlobal(QPoint(0,0)).y()<<ui->W5T2->size();
    qDebug()<<ui->W5C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5C1->mapToGlobal(QPoint(0,0)).y()<<ui->W5C1->size();
    qDebug()<<ui->W5C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5C2->mapToGlobal(QPoint(0,0)).y()<<ui->W5C2->size();
    qDebug()<<ui->W5C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5C3->mapToGlobal(QPoint(0,0)).y()<<ui->W5C3->size();
    qDebug()<<ui->W5N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5N1->mapToGlobal(QPoint(0,0)).y()<<ui->W5N1->size();
    qDebug()<<ui->W5N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W5N2->mapToGlobal(QPoint(0,0)).y()<<ui->W5N2->size();
    qDebug()<<"W6";
    qDebug()<<ui->W6T1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6T1->mapToGlobal(QPoint(0,0)).y()<<ui->W6T1->size();
    qDebug()<<ui->W6T2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6T2->mapToGlobal(QPoint(0,0)).y()<<ui->W6T2->size();
    qDebug()<<ui->W6C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6C1->mapToGlobal(QPoint(0,0)).y()<<ui->W6C1->size();
    qDebug()<<ui->W6C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6C2->mapToGlobal(QPoint(0,0)).y()<<ui->W6C2->size();
    qDebug()<<ui->W6C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6C3->mapToGlobal(QPoint(0,0)).y()<<ui->W6C3->size();
    qDebug()<<ui->W6N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6N1->mapToGlobal(QPoint(0,0)).y()<<ui->W6N1->size();
    qDebug()<<ui->W6N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W6N2->mapToGlobal(QPoint(0,0)).y()<<ui->W6N2->size();
    qDebug()<<"W7";
    qDebug()<<ui->pushButton->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton->size();
    qDebug()<<ui->pushButton_12->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_12->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_12->size();
    qDebug()<<ui->pushButton_13->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_13->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_13->size();
    qDebug()<<ui->pushButton_14->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->pushButton_14->mapToGlobal(QPoint(0,0)).y()<<ui->pushButton_14->size();
    qDebug()<<ui->comboBox->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->comboBox->mapToGlobal(QPoint(0,0)).y()<<ui->comboBox->size();
    qDebug()<<ui->W7N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W7N1->mapToGlobal(QPoint(0,0)).y()<<ui->W7N1->size();
    qDebug()<<ui->W7N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W7N2->mapToGlobal(QPoint(0,0)).y()<<ui->W7N2->size();
    qDebug()<<"W8";
    qDebug()<<ui->W8C1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C1->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C1->size();
    qDebug()<<ui->W8C2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C2->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C2->size();
    qDebug()<<ui->W8C3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C3->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C3->size();
    qDebug()<<ui->W8C4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C4->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C4->size();
    qDebug()<<ui->W8C5->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C5->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C5->size();
    qDebug()<<ui->W8C6->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8C6->mapToGlobal(QPoint(0,0)).y()<<" "<<ui->W8C6->size();
    qDebug()<<ui->W8N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8N1->mapToGlobal(QPoint(0,0)).y()<<ui->W8N1->size();
    qDebug()<<ui->W8N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W8N2->mapToGlobal(QPoint(0,0)).y()<<ui->W8N2->size();
    qDebug()<<"W9";
    qDebug()<<ui->W9T1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9T1->mapToGlobal(QPoint(0,0)).y()<<ui->W9T1->size();
    qDebug()<<ui->W9T2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9T2->mapToGlobal(QPoint(0,0)).y()<<ui->W9T2->size();
    qDebug()<<ui->W9T3->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9T3->mapToGlobal(QPoint(0,0)).y()<<ui->W9T3->size();
    qDebug()<<ui->W9T4->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9T4->mapToGlobal(QPoint(0,0)).y()<<ui->W9T4->size();
    qDebug()<<ui->W9N1->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9N1->mapToGlobal(QPoint(0,0)).y()<<ui->W9N1->size();
    qDebug()<<ui->W9N2->mapToGlobal(QPoint(0,0)).x()<<" "<<ui->W9N2->mapToGlobal(QPoint(0,0)).y()<<ui->W9N2->size();

}

int factorial(int n) {
    if(n == 0) return 1;
    return n * factorial(n-1);
}
void iterPermutation(vector<int> &list, int l, int h, vector<int> &ret, int &k) {
    if(l > h) {
        k--;
        if(k == 0) ret = list;
        return;
    }
    for(int i = l; i <= h; i++) {
        swap(list[i], list[l]);
        iterPermutation(list, l+1, h, ret, k);
        swap(list[i], list[l]);
    }
}
void f3::ShowPhoto(int parm)
{
    ui->S1->hide();ui->S2->hide();
    ui->S3->hide();ui->S4->hide();
    ui->S1L->hide();ui->S2L->hide();
    ui->S3L->hide();ui->S4L->hide();
    auto v = picshow[type];
    ph_now = (ph_now+parm+v.size())%v.size();
    if(v[ph_now]=="1")
    {
        movie->setPaused(true);
        ui->W3S->clear();
        ui->S1->show();ui->S2->show();
        ui->S3->show();ui->S4->show();
        ui->S1L->show();ui->S2L->show();
        ui->S3L->show();ui->S4L->show();
        return;
    }


    if(v[ph_now].at(v[ph_now].size()-1)=='f')
    {
        ui->W3S->clear();
        movie->setFileName("./p/"+v[ph_now]);
        ui->W3S->setMovie(movie);
        movie->start();
    }
    else
    {
        movie->setPaused(true);
        //cout<<2<<endl;
        QString sc = "./p/"+v[ph_now];
        //cout<<"tpmz:"<<sc.toStdString()<<endl;
        QPixmap pixmap("./p/"+v[ph_now]);
        //cout<<3<<endl;
        //cout<<QDir::currentPath().toStdString()<<endl;
        //pixmap = pixmap.scaled(ui->W3S->size(),Qt::KeepAspectRatio);
        ui->W3S->setPixmap(pixmap);
    }
    //ui->W3S->setScaledContents(true);
}

f3::~f3()
{
    delete ui;
}

void f3::initpt()
{
    srand((int)time(0));
    vector<int>vec;
    for(int i = 1; i < 5; i++) vec.push_back(i);
    vector<int>ret;
    while(ret.size()<4||(ret[0]==1&&ret[1]==2&&ret[2]==3&&ret[3]==4))
    {
        int r = rand() % factorial(4);
        iterPermutation(vec, 0, 3, ret, r);
        S1 = ret[0];S2=ret[1];S3=ret[2];S4=ret[3];
    }
    if(modeltype==1)
        S1 = 1,S2 = 2,S3 = 3,S4 = 4;
    ui->comboBox->addItem(QString::number(1));
    ui->comboBox->addItem(QString::number(2));
    ui->comboBox->addItem(QString::number(3));
    ui->comboBox->addItem(QString::number(4));
    picmap[S1] = 1;picmap[S2] = 2;picmap[S3] = 3;picmap[S4] = 4;
    picmap1[1] = S1;picmap1[2] = S2;picmap1[3] = S3;picmap1[4] = S4;
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
    ui->S1->setGeometry(50,50,370,200);
    ui->S2->setGeometry(420,51,370,200);
    ui->S3->setGeometry(50,250,370,200);
    ui->S4->setGeometry(420,250,370,200);
    ui->S1->hide();ui->S2->hide();
    ui->S3->hide();ui->S4->hide();
    ui->S1L->hide();ui->S2L->hide();
    ui->S3L->hide();ui->S4L->hide();
    ui->W3->setDisabled(true);
}

void f3::update(QString w, vector<pair<QString,vector<QString>>> content=vector<pair<QString,vector<QString>>>())
{
//    cout<<w.toStdString()<<endl;
//    for(auto i:content)
//    {
//        cout<<" "<<i.first.toStdString()<<endl;
//        for(auto j:i.second)
//        {
//            cout<<"  "<<j.toStdString()<<endl;
//        }
//    }
    //qDebug()<<"color:"<<wz+"rgb(162, 162, 162);";
    ui->W2S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W2C1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W2C2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W2C3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W2C4->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");

    ui->W5S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5S2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5L1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5L2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5C1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5C2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W5C3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");

    ui->W6S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6S2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6L1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6L2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6C1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6C2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W6C3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");

    ui->W7S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");


    ui->W8S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C4->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C5->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W8C6->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");

    ui->W9S->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W9L1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W9L2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W9L3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W9L4->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");

    if(w=="W2")
    {
        ui->W2S->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W2C1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W2C2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W2C3->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W2C4->setStyleSheet("""font-size:12pt;""color:white;");
        ans.clear();
        for(auto i:content)
        {
            if(i.first=="W2S")
            {
                ui->W2S->setText(i.second[0]);
            }
            else if(i.first=="W2N1")
                ui->W2N1->setText(i.second[0]);
            else if(i.first=="W2N2")
                ui->W2N2->setText(i.second[0]);
            else if(i.first=="W2C1")
                ui->W2C1->setText(i.second[0]);
            else if(i.first=="W2C2")
                ui->W2C2->setText(i.second[0]);
            else if(i.first=="W2C3")
                ui->W2C3->setText(i.second[0]);
            else if(i.first=="W2C4")
                ui->W2C4->setText(i.second[0]);
            else if(i.first=="W2CA")
            {
                int acc = 0;
                for(int j=0;j<i.second.size();++j)
                {
                    if(i.second[j]=="1")
                        acc = j+1;
                }
                ans.push_back(QString::number(acc));

//                int acc = 0;
//                auto Jp = MR.GetJump(w);
//                if(now_model+1<Model.size())
//                {
//                    for(int j=0;j<i.second.size();++j)
//                    {
//                        if(i.second[j]=="1")
//                            acc = j+1;
//                    }
//                    QString idx;
//                    for(auto j:Jp)
//                        if(j.second==Model[now_model+1])
//                            idx = j.first;
//                    ans.push_back(idx);
//                    QString mid,cnt;
//                    if(idx=="1") mid = ui->W2C1->text();
//                    if(idx=="2") mid = ui->W2C2->text();
//                    if(idx=="3") mid = ui->W2C3->text();
//                    if(idx=="4") mid = ui->W2C4->text();
//                    if(acc==1) cnt = ui->W2C1->text();
//                    if(acc==2) cnt = ui->W2C2->text();
//                    if(acc==3) cnt = ui->W2C3->text();
//                    if(acc==4) cnt = ui->W2C4->text();
//                    if(idx=="1") ui->W2C1->setText(cnt);
//                    if(idx=="2") ui->W2C2->setText(cnt);
//                    if(idx=="3") ui->W2C3->setText(cnt);
//                    if(idx=="4") ui->W2C4->setText(cnt);
//                    if(acc==1) ui->W2C1->setText(mid);
//                    if(acc==2) ui->W2C2->setText(mid);
//                    if(acc==3) ui->W2C3->setText(mid);
//                    if(acc==4) ui->W2C4->setText(mid);
//                }

            }
        }
    }
    else if(w=="W5")
    {
        ui->W5S->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5S2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5L1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5L2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5C1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5C2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5C3->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W5T1->setEnabled(1);
        ui->W5T2->setEnabled(1);
        ui->W5T1->clear();
        ui->W5T2->clear();
        ui->W5C1->setEnabled(1);
        ui->W5C2->setEnabled(1);
        ui->W5C3->setEnabled(1);
        ans.clear();
        for(auto i:content)
        {
            if(i.first=="W5S")
            {
                cout<<91<<endl;
                ui->W5S->setText(i.second[0]);
                cout<<92<<endl;
            }
            else if(i.first=="W5N1")
            {
                cout<<93<<endl;
                ui->W5N1->setText(i.second[0]);
                cout<<94<<endl;
            }
            else if(i.first=="W5N2")
                ui->W5N2->setText(i.second[0]);
            else if(i.first=="W5L1")
                ui->W5L1->setText(i.second[0]);
            else if(i.first=="W5T1")
                for(auto j:i.second)
                    ui->W5T1->addItem(j);
            else if(i.first=="W5T1A")
                ans.push_back(i.second[0]);
            else if(i.first=="W5T2")
                for(auto j:i.second)
                    ui->W5T2->addItem(j);
            else if(i.first=="W5T2A")
                ans.push_back(i.second[0]);
            else if(i.first=="W5L2")
                ui->W5L2->setText(i.second[0]);
            else if(i.first=="W5S2")
                ui->W5S2->setText(i.second[0]);
            else if(i.first=="W5C1")
                ui->W5C1->setText(i.second[0]);
            else if(i.first=="W5C2")
                ui->W5C2->setText(i.second[0]);
            else if(i.first=="W5C3")
                ui->W5C3->setText(i.second[0]);
        }
//        if(Model[now_model+1]=="W8")
//        {
//            ui->W5S2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
//            ui->W5C1->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
//            ui->W5C2->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
//            ui->W5C3->setStyleSheet("""font-size:12pt;""color:rgb(162, 162, 162);");
//            ui->W5C1->setDisabled(1);
//            ui->W5C2->setDisabled(1);
//            ui->W5C3->setDisabled(1);
//            ui->W5C1->setEnabled(false);
//            ui->W5C2->setEnabled(false);
//            ui->W5C3->setEnabled(false);
//        }
    }
    else if(w=="W6")
    {
        ui->W6S->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6S2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6L1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6L2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6C1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6C2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6C3->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W6T1->setEnabled(1);
        ui->W6T2->setEnabled(1);
        ui->W6C1->setEnabled(1);
        ui->W6C2->setEnabled(1);
        ui->W6C3->setEnabled(1);
        for(auto i:content)
        {
            if(i.first=="W6S")
                ui->W6S->setText(i.second[0]);
            else if(i.first=="W6N1")
                ui->W6N1->setText(i.second[0]);
            else if(i.first=="W6N2")
                ui->W6N2->setText(i.second[0]);
            else if(i.first=="W6L1")
                ui->W6L1->setText(i.second[0]);
            else if(i.first=="W6L2")
                ui->W6L2->setText(i.second[0]);
            else if(i.first=="W6T1")
                ui->W6T1->setText(i.second[0]);
            else if(i.first=="W6T2")
                ui->W6T2->setText(i.second[0]);
            else if(i.first=="W6S2")
                ui->W6S2->setText(i.second[0]);
            else if(i.first=="W6C1")
                ui->W6C1->setText(i.second[0]);                
            else if(i.first=="W6C2")
                ui->W6C2->setText(i.second[0]);
            else if(i.first=="W6C3")
                ui->W6C3->setText(i.second[0]);
            else if(i.first=="W6CA" && Model[now_model]=="W6")
            {
                int acc = 0;
                auto Jp = MR.GetJump(w);
                if(now_model+1<Model.size())
                {
                    for(int j=0;j<i.second.size();++j)
                    {
                        if(i.second[j]=="1")
                            acc = j+1;
                    }
                    QString idx;
                    for(auto j:Jp)
                        if(j.second==Model[now_model+1])
                            idx = j.first;
                    QString mid,cnt;
                    if(idx=="1") mid = ui->W6C1->text();
                    if(idx=="2") mid = ui->W6C2->text();
                    if(idx=="3") mid = ui->W6C3->text();
                    if(acc==1) cnt = ui->W6C1->text();
                    if(acc==2) cnt = ui->W6C2->text();
                    if(acc==3) cnt = ui->W6C3->text();
                    if(idx=="1") ui->W6C1->setText(cnt);
                    if(idx=="2") ui->W6C2->setText(cnt);
                    if(idx=="3") ui->W6C3->setText(cnt);
                    if(acc==1) ui->W6C1->setText(mid);
                    if(acc==2) ui->W6C2->setText(mid);
                    if(acc==3) ui->W6C3->setText(mid);
                }

            }
        }
    }
    else if(w=="W7")
    {
        ui->W7S->setStyleSheet("""font-size:12pt;""color:white;");
        for(auto i:content)
        {
            if(i.first=="W7S")
                ui->W7S->setText(i.second[0]);
            else if(i.first=="W7N1")
                ui->W7N1->setText(i.second[0]);
            else if(i.first=="W7N2")
                ui->W7N2->setText(i.second[0]);
        }
    }
    else if(w=="W8")
    {
        ui->W8S->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C3->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C4->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C5->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W8C6->setStyleSheet("""font-size:12pt;""color:white;");

        for(auto i:content)
        {
            if(i.first=="W8S")
                ui->W8S->setText(i.second[0]);
            else if(i.first=="W8N1")
                ui->W8N1->setText(i.second[0]);
            else if(i.first=="W8N2")
                ui->W8N2->setText(i.second[0]);
            else if(i.first=="W8C1")
                ui->W8C1->setText(i.second[0]);
            else if(i.first=="W8C2")
                ui->W8C2->setText(i.second[0]);
            else if(i.first=="W8C3")
                ui->W8C3->setText(i.second[0]);
            else if(i.first=="W8C4")
                ui->W8C4->setText(i.second[0]);
            else if(i.first=="W8C5")
                ui->W8C5->setText(i.second[0]);
            else if(i.first=="W8C6")
                ui->W8C6->setText(i.second[0]);
            else if(i.first=="W8C")
            {
                ui->W8C1->setText(i.second[0]);
                ui->W8C2->setText(i.second[1]);
                ui->W8C3->setText(i.second[2]);
                ui->W8C4->setText(i.second[3]);
                ui->W8C5->setText(i.second[4]);
                ui->W8C6->setText(i.second[5]);
            }
        }
        if(Model[now_model+1]=="W7")
        {
            QString m = ui->W8C5->text();
            ui->W8C5->setText(ui->W8C1->text());
            ui->W8C1->setText(m);
        }
    }
    else if(w=="W9")
    {
        ui->W9S->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W9L1->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W9L2->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W9L3->setStyleSheet("""font-size:12pt;""color:white;");
        ui->W9L4->setStyleSheet("""font-size:12pt;""color:white;");
        ans.clear();
        for(auto i:content)
        {
            if(i.first=="W9S")
                ui->W9S->setText(i.second[0]);
            else if(i.first=="W9N1")
                ui->W9N1->setText(i.second[0]);
            else if(i.first=="W9N2")
                ui->W9N2->setText(i.second[0]);
            else if(i.first=="W9L1")
                ui->W9L1->setText(i.second[0]);
            else if(i.first=="W9L2")
                ui->W9L2->setText(i.second[0]);
            else if(i.first=="W9L3")
                ui->W9L3->setText(i.second[0]);
            else if(i.first=="W9L4")
                ui->W9L4->setText(i.second[0]);
            else if(i.first=="W9A")
            {
                for(auto j:i.second)
                    ans.push_back(j);
            }
        }
    }
}
void f3::MakeUse(QString name)
{
    ui->W1->setDisabled(true);
    ui->W2->setDisabled(true);
    ui->W5->setDisabled(true);
    ui->W6->setDisabled(true);
    ui->W7->setDisabled(true);
    ui->W8->setDisabled(true);
    ui->W8->setDisabled(true);
    ui->W9->setDisabled(true);
    if(name=="W1")
    {
        ui->W1->setEnabled(true);
        ui->W1C1->setDisabled(true);
        ui->W1C2->setDisabled(true);
        ui->W1C3->setDisabled(true);
        ui->W1C4->setDisabled(true);
        ui->W1C1->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
        ui->W1C2->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
        ui->W1C3->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
        ui->W1C4->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");

        if(type=="1")
        {
            ui->W1C1->setEnabled(true);
            ui->W1C1->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
        }
        if(type=="2")
        {
            ui->W1C2->setEnabled(true);
            ui->W1C2->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
        }
        if(type=="3")
        {
            ui->W1C3->setEnabled(true);
            ui->W1C3->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
        }
        if(type=="4")
        {
            ui->W1C4->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
            ui->W1C4->setEnabled(true);
        }
    }
    if(name=="W2")
    {
        ui->W2->setEnabled(true);
    }
    if(name=="W4")
        ui->W4->setEnabled(true);
    if(name=="W5")
    {
        ui->W5->setEnabled(true);
    }
    if(name=="W6")
    {
        ui->W6->setEnabled(true);
    }
    if(name=="W7")
    {
        ui->W7->setEnabled(true);

    }
    if(name=="W8")
    {
        ui->W8->setEnabled(true);
    }
    if(name=="W9")
    {
        ui->W9->setEnabled(true);
    }
}

bool f3::NxtStep(QString parm)
{
    //auto a = MR.NextStep(parm,type);
    if(parm!="0")
        now_model++;
    RET a;
    if(now_model>=Model.size())
        a = MR.NextStep("W1","1");
    else
        a = MR.NextStep(Model[now_model],type);
    if(a.Dia=="NaN")
        return 0;
    //cout<<"now:"<<now_model<<" "<< Model[now_model].toStdString()<<" "<<parm.toStdString()<<" "<<a.Dia.toStdString()<<endl;
    update(a.Dia,a.dd);
    MakeUse(a.Dia);

    return 1;
}
void f3::undo()
{
    auto i = MR.undo();
    if(i=="NaN")
        return;
    update(i);
    MakeUse(i);
    now_model--;
}

void f3::AllClear()
{
    ui->W2S->clear();
    ui->W2C1->setCheckable(false);
    ui->W2C2->setCheckable(false);
    ui->W2C3->setCheckable(false);
    ui->W2C4->setCheckable(false);
    ui->W2C1->setCheckable(true);
    ui->W2C2->setCheckable(true);
    ui->W2C3->setCheckable(true);
    ui->W2C4->setCheckable(true);

    ui->W2C1->setText("");
    ui->W2C2->setText("");
    ui->W2C3->setText("");
    ui->W2C4->setText("");

    ui->W3->setDisabled(true);
    auto v = picshow[type];
    if(v[ph_now].at(v[ph_now].size()-1)=='f')
        ShowPhoto(-1);

    ui->W5S->clear();
    ui->W5S2->clear();
    ui->W5C1->setChecked(false);
    ui->W5C2->setChecked(false);
    ui->W5C3->setChecked(false);
    ui->W5L1->clear();
    ui->W5L2->clear();
    ui->W5T1->clear();
    ui->W5T2->clear();
    ui->W5C1->setText("");
    ui->W5C2->setText("");
    ui->W5C3->setText("");

    ui->W6S->clear();
    ui->W6S2->clear();
    ui->W6C1->setCheckable(false);
    ui->W6C2->setCheckable(false);
    ui->W6C3->setCheckable(false);
    ui->W6C1->setCheckable(true);
    ui->W6C2->setCheckable(true);
    ui->W6C3->setCheckable(true);
    ui->W6L1->clear();
    ui->W6L2->clear();
    ui->W6T1->clear();
    ui->W6T2->clear();
    ui->W6C1->setText("");
    ui->W6C2->setText("");
    ui->W6C3->setText("");

    ui->W7S->clear();

    ui->W8S->clear();
    ui->W8C1->setText("");
    ui->W8C2->setText("");
    ui->W8C3->setText("");
    ui->W8C4->setText("");
    ui->W8C5->setText("");
    ui->W8C6->setText("");
    ui->W8C1->setChecked(false);
    ui->W8C2->setChecked(false);
    ui->W8C3->setChecked(false);
    ui->W8C4->setChecked(false);
    ui->W8C5->setChecked(false);
    ui->W8C6->setChecked(false);

    ui->W9S->clear();
    ui->W9L1->clear();
    ui->W9L2->clear();
    ui->W9L3->clear();
    ui->W9L4->clear();
    ui->W9T1->clear();
    ui->W9T2->clear();
    ui->W9T3->clear();
    ui->W9T4->clear();


    srand((int)time(0));
    vector<int>vec;
    for(int i = 1; i < 5; i++) vec.push_back(i);
    vector<int>ret;
    while(ret.size()<4||(ret[0]==1&&ret[1]==2&&ret[2]==3&&ret[3]==4))
    {
        int r = rand() % factorial(4);
        iterPermutation(vec, 0, 3, ret, r);
        S1 = ret[0];S2=ret[1];S3=ret[2];S4=ret[3];
    }

    //picmap[S1] = 1;picmap[S2] = 2;picmap[S3] = 3;picmap[S4] = 4;
    //picmap1[1] = S1;picmap1[2] = S2;picmap1[3] = S3;picmap1[4] = S4;
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
}

void f3::on_W2N_clicked()
{
    if(ui->W2C1->isChecked()==0 && ui->W2C2->isChecked()==0 && ui->W2C3->isChecked()==0&&ui->W2C4->isChecked()==0)
        return;
    auto ashow = MR.all(type);
    ui->W3S->show();
    for(auto i:ashow)
    {
        update(i.Dia,i.dd);
    }
    if(ui->W2C1->isChecked())
        NxtStep("1");
    else if(ui->W2C2->isChecked())
        NxtStep("2");
    else if(ui->W2C3->isChecked())
        NxtStep("3");
    else if(ui->W2C4->isChecked())
        NxtStep("4");

}

void f3::on_W5N_clicked()
{
    if(ui->W5T1->currentText()!=ans[0] || ui->W5T2->currentText()!=ans[1])
        return;
    int parm = 0;
    if(ui->W5C1->isChecked())
        parm+=4;
    if(ui->W5C2->isChecked())
        parm+=2;
    if(ui->W5C3->isChecked())
        parm+=1;
    if(parm !=0 )
        NxtStep(QString::number(parm));
}

void f3::on_W6N_clicked()
{
    if(ui->W6C1->isChecked())
        NxtStep("1");
    else if(ui->W6C2->isChecked())
        NxtStep("2");
    else if(ui->W6C3->isChecked())
        NxtStep("3");
    //NxtStep("1");
}

void f3::on_W8N_clicked()
{
    if(ui->W8C1->isChecked() && ui->W8C2->isChecked()&& ui->W8C3->isChecked()&&ui->W8C4->isChecked()&&ui->W8C5->isChecked()&&ui->W8C6->isChecked()==0)
    {
        bool cc = NxtStep("2");
        if(!cc)
            NxtStep("1");
    }
    else
        NxtStep("1");
}

void f3::on_W9N_clicked()
{
    NxtStep("1");
}

void f3::on_pushButton_4_clicked()
{
    ShowPhoto(-1);
    timer->start(10000);
}

void f3::on_pushButton_6_clicked()
{
    ShowPhoto(1);
    timer->start(10000);
}



void f3::on_W7N_clicked()
{
    if(S1==1 &&S2==2 &&S3==3 &&S4==4)
        NxtStep("1");
}

void f3::on_comboBox_activated(int index)
{

    if(index==0)
    {

    }


}



void f3::on_pushButton_clicked()
{
    int index = ui->comboBox->currentIndex()+1;
    //index = picmap1[index];
    if(S3==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S1)+".png");
        image1 = image1.scaled(ui->S1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S1->setPixmap(image1);
        ui->S3->setPixmap(image2);
        S3 = S1;
        S1 = index;
    }
    else if(S4==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S2)+".png");
        image1 = image1.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S2->setPixmap(image1);
        ui->S4->setPixmap(image2);
        S4 = S2;
        S2 = index;
    }
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
    timer->start(10000);
}

void f3::on_pushButton_12_clicked()
{
    int index = ui->comboBox->currentIndex()+1;
    //index = picmap1[index];
    if(S2==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S1)+".png");
        image1 = image1.scaled(ui->S1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S1->setPixmap(image1);
        ui->S2->setPixmap(image2);
        S2 = S1;
        S1 = index;
    }
    else if(S4==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S3)+".png");
        image1 = image1.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S3->setPixmap(image1);
        ui->S4->setPixmap(image2);
        S4 = S3;
        S3 = index;
    }
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
    timer->start(10000);
}

void f3::on_pushButton_13_clicked()
{
    int index = ui->comboBox->currentIndex()+1;
    //index = picmap1[index];
    if(S1==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S2)+".png");
        image1 = image1.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S2->setPixmap(image1);
        ui->S1->setPixmap(image2);
        S1 = S2;
        S2 = index;
    }
    else if(S3==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S4)+".png");
        image1 = image1.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S4->setPixmap(image1);
        ui->S3->setPixmap(image2);
        S3 = S4;
        S4 = index;
    }
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
    timer->start(10000);
}

void f3::on_pushButton_14_clicked()
{
    int index = ui->comboBox->currentIndex()+1;
    //index = picmap1[index];
    if(S1==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S3)+".png");
        image1 = image1.scaled(ui->S1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S3->setPixmap(image1);
        ui->S1->setPixmap(image2);
        S1 = S3;
        S3 = index;
    }
    else if(S2==index)
    {
        QPixmap image1("./p/pt/"+type+"/"+QString::number(index)+".png");
        QPixmap image2("./p/pt/"+type+"/"+QString::number(S4)+".png");
        image1 = image1.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        image2 = image2.scaled(ui->S4->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->S4->setPixmap(image1);
        ui->S2->setPixmap(image2);
        S2 = S4;
        S4 = index;
    }
    ui->S1L->setText(QString::number(S1));
    ui->S2L->setText(QString::number(S2));
    ui->S3L->setText(QString::number(S3));
    ui->S4L->setText(QString::number(S4));
    timer->start(10000);
}

void f3::on_W5N1_clicked()
{
    undo();
}

void f3::on_W2N2_clicked()
{
    if(ui->W2C1->isChecked()==0 && ui->W2C2->isChecked()==0 && ui->W2C3->isChecked()==0&&ui->W2C4->isChecked()==0)
        return;
    if(ans[0]=="1"&&ui->W2C1->isChecked()==0)return;
    if(ans[0]=="2"&&ui->W2C2->isChecked()==0)return;
    if(ans[0]=="3"&&ui->W2C3->isChecked()==0)return;
    if(ans[0]=="4"&&ui->W2C4->isChecked()==0)return;
    cout<<ans[0].toStdString()<<endl;
    cout<<"showall"<<endl;
    auto ashow = MR.all(type);
    ui->W3S->show();
    ph_now = 0;
    ShowPhoto(0);
    for(auto i:ashow)
    {
        update(i.Dia,i.dd);
    }
    cout<<"fin:showall"<<endl;
//    if(ui->W2C1->isChecked())
//    {
//        NxtStep("1");
//    }
//    else if(ui->W2C2->isChecked())
//    {
//        NxtStep("2");
//    }
//    else if(ui->W2C3->isChecked())
//    {
//        NxtStep("3");
//    }
//    else if(ui->W2C4->isChecked())
//    {
//        NxtStep("4");
//    }
    NxtStep();
    QPixmap image1("./p/pt/"+type+"/"+QString::number(S1)+".png");
    image1 = image1.scaled(370,200,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->S1->setPixmap(image1);
    ui->S1->setAlignment(Qt::AlignRight);
    QPixmap image2("./p/pt/"+type+"/"+QString::number(S2)+".png");
    image2 = image2.scaled(ui->S2->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->S2->setPixmap(image2);
    ui->S2->setAlignment(Qt::AlignLeft);
    QPixmap image3("./p/pt/"+type+"/"+QString::number(S3)+".png");
    image3 = image3.scaled(ui->S3->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->S3->setPixmap(image3);
    ui->S3->setAlignment(Qt::AlignRight);
    QPixmap image4("./p/pt/"+type+"/"+QString::number(S4)+".png");
    image4 = image4.scaled(ui->S4->size(),Qt::KeepAspectRatio);
    ui->S4->setPixmap(image4);
    ui->S4->setAlignment(Qt::AlignLeft);
    int l = image4.size().width();
    ui->S1L->setGeometry(395-l,60,50,30);
    ui->S2L->setGeometry(430+l,60,50,30);
    ui->S3L->setGeometry(395-l,440,50,30);
    ui->S4L->setGeometry(430+l,440,50,30);
    ui->W3->setEnabled(true);
}

void f3::on_W1C1_clicked()
{
    type = "1";
    NxtStep("0");
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));
}

void f3::on_W1C2_clicked()
{
    type = "2";
    NxtStep("0");
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));
}

void f3::on_W1C3_clicked()
{
    type = "3";
    NxtStep("0");
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));
}

void f3::on_W1C4_clicked()
{
    type = "4";
    NxtStep("0");
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));
}

void f3::on_W8N2_clicked()
{
    if(ui->W8C1->isChecked() || ui->W8C2->isChecked()|| ui->W8C3->isChecked()||ui->W8C4->isChecked()||ui->W8C5->isChecked()||ui->W8C6->isChecked())
        NxtStep();
    else
        return;
//    if(ui->W8C1->isChecked() && ui->W8C2->isChecked()&& ui->W8C3->isChecked()&&ui->W8C4->isChecked()&&ui->W8C5->isChecked()&&ui->W8C6->isChecked()==0)
//    {
//        bool cc = NxtStep("2");
//        if(!cc)
//            NxtStep("1");
//    }
//    else
//        NxtStep("1");
}

void f3::on_W2N1_clicked()
{
    undo();
}

void f3::on_W6N1_clicked()
{
    undo();
}

void f3::on_W7N1_clicked()
{
    undo();
}

void f3::on_W8N1_clicked()
{
    undo();
}

void f3::on_W9N1_clicked()
{
    undo();
}

void f3::on_W5N2_clicked()
{
    if(ui->W5C1->isChecked()==false && ui->W5C2->isChecked()==false && ui->W5C3->isChecked()==false)
        return;
    if(ui->W5T1->currentText()!=ans[0] || ui->W5T2->currentText()!=ans[1])
        return;
    int parm = 0;
    if(ui->W5C1->isChecked())
        parm+=4;
    if(ui->W5C2->isChecked())
        parm+=2;
    if(ui->W5C3->isChecked())
        parm+=1;
    //NxtStep(QString::number(parm));
    NxtStep();
}

void f3::on_W6N2_clicked()
{
    if(!ui->W6C1->isChecked() && !ui->W6C2->isChecked() && !ui->W6C3->isChecked())
        return;
    if(ui->W6T1->text()=="" || ui->W6T1->text()=="")
        return;
    NxtStep();
//    if(ui->W6C1->isChecked())
//        NxtStep("1");
//    else if(ui->W6C2->isChecked())
//        NxtStep("2");
//    else if(ui->W6C3->isChecked())
//        NxtStep("3");
}

void f3::on_W7N2_clicked()
{
    if(S1==1 &&S2==2 &&S3==3 &&S4==4)
        NxtStep("1");
}

void f3::on_W9N2_clicked()
{
    if(ui->W9T1->text()=="" || ui->W9T2->text()=="" || ui->W9T3->text()=="" || ui->W9T4->text()=="")
        return;
    NxtStep();
    now_model = 0;
    modeltype = (modeltype+1)%8;
    if(modeltype==0)
    {modeltype=1;needtimes--;}
    Model = MR.GetModel(modeltype);
    if(modeltype==1)
        S1 = 1,S2 = 2,S3 = 3,S4 = 4;
    if(type=="1")
        type = "2";
    else if(type=="2")
        type = "3";
    else if(type=="3")
        type = "4";
    else if(type=="4")
        type = "1";
    MakeUse("W1");
    AllClear();
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));

}

void f3::on_pushButton_5_clicked()
{
    timer->start(10000);
    movie->setPaused(false);
}

void f3::on_pushButton_11_clicked()
{
    timer->start(10000);
    movie->setPaused(true);
}

void f3::on_W4N_clicked()
{
    modeltype = ui->W4CL->text().toInt();
    Model = MR.GetModel(modeltype);
    type = ui->W4CS->text();
    needtimes = 14;
    ID = ui->ID->text();
    if(ID.length()==1)
        ID = "0"+ID;
    ui->AS->setText("ID："+ID+"  MD："+type+"  LOGIC："+ QString::number(modeltype)+" LAST"+QString::number(needtimes));
    ui->W1->setEnabled(true);
    ui->W1C1->setDisabled(true);
    ui->W1C2->setDisabled(true);
    ui->W1C3->setDisabled(true);
    ui->W1C4->setDisabled(true);
    ui->W1C1->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C2->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C3->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");
    ui->W1C4->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:rgb(162, 162, 162);");

    if(type=="1")
    {
        ui->W1C1->setEnabled(true);
        ui->W1C1->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
    }
    if(type=="2")
    {
        ui->W1C2->setEnabled(true);
        ui->W1C2->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
    }
    if(type=="3")
    {
        ui->W1C3->setEnabled(true);
        ui->W1C3->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
    }
    if(type=="4")
    {
        ui->W1C4->setStyleSheet("border-image:url(:/p/1/sb.png);""background: transparent;""""font-size:12pt;""color:white;");
        ui->W1C4->setEnabled(true);
    }

}
