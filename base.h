#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
//#include "openglwidget.h"
//#include "board.h"
#include <QBitmap>
QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);


    ~Base();

private slots:
    void on_pushButton_clicked();

   // void on_pushButton_2_clicked();

private:
    Ui::Base *ui;

};

#endif // BASE_H
