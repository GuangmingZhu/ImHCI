#ifndef F2_H
#define F2_H
#include <QScrollArea>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class f2;
}

class f2 : public QWidget
{
    Q_OBJECT

public:
    explicit f2(QWidget *parent = 0);
    ~f2();
private slots:
    void on_timer();
    void on_C1_clicked();
    void on_C2_clicked();
    void on_C3_clicked();
    void on_C4_clicked();
    void on_C5_clicked();
    void on_C6_clicked();
    void on_C7_clicked();
    void on_C8_clicked();


private:
    Ui::f2 *ui;
    QTimer *timer;
    QStringList picList;
    QPixmap picture;




};

#endif // F2_H
