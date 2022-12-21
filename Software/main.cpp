#include "mainwindow.h"
#include <QApplication>
#include <initdia.h>
#include <QDebug>
#include "f2.h"
#include "f3.h"
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    QDesktopWidget* desktop = QApplication::desktop();
   //w.show();
    //InitDia initdia(&w);
    //std::cout<<initdia.ReadJson("./prop.json")<<std::endl;
    f2 f1;
    f3 f;
    if(desktop->screenCount()>=2)
    {
        f1.setGeometry(desktop->screenGeometry(0));
        f.setGeometry(desktop->screenGeometry(1));
    }
    f1.show();
    f.show();
    return a.exec();

}
