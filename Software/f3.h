#ifndef F3_H
#define F3_H
#include <QTimer>
#include <QWidget>
#include <vector>
#include<modelrun.h>
#include<QMovie>

using namespace std;
namespace Ui {
class f3;
}

class f3 : public QWidget
{
    Q_OBJECT

public:
    explicit f3(QWidget *parent = 0);
    ~f3();
    void update(QString w,vector<pair<QString,vector<QString>>>content);
private slots:
    void on_W2N_clicked();

    void on_W5N_clicked();

    void on_W6N_clicked();

    void on_W7N_clicked();

    void on_W8N_clicked();

    void on_W9N_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();


    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_W5N1_clicked();

    void on_W2N2_clicked();

    void on_W1C1_clicked();

    void on_W1C2_clicked();

    void on_W1C3_clicked();

    void on_W1C4_clicked();

    void on_W8N2_clicked();

    void on_W2N1_clicked();

    void on_W6N1_clicked();

    void on_W7N1_clicked();

    void on_W8N1_clicked();

    void on_W9N1_clicked();

    void on_W5N2_clicked();

    void on_W6N2_clicked();

    void on_W7N2_clicked();

    void on_W9N2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_W4N_clicked();

private:
    Ui::f3 *ui;
    ModelRun MR;
    int ph_now;
    QString wz = "font-size:12pt;color:";
    vector<QString> bof;
    map<QString,vector<QString>> picshow;
    int S1=1,S2=2,S3=3,S4=4;
    vector<QString> Model;
    int now_model;
    int modeltype;
    QTimer *timer;
    QMovie *movie = new QMovie;
    vector<QString> ans;
    map<int,int>picmap,picmap1;
    QString type;
    QString ID;
    int now_s;
    int needtimes;

    bool NxtStep(QString parm = "1");
    void ShowPhoto(int parm);
    void initpt();
    void MakeUse(QString name);
    void undo();
    void AllClear();
};

#endif // F3_H
