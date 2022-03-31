#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include "openglwidget.h"
#include <QBitmap>
namespace Ui {
class Board;
}

class Board : public QMainWindow
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    void change_color();

private slots:
    void on_pushButton_clicked(bool checked);



    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_6_clicked(bool checked);

    void on_pushButton_7_clicked(bool checked);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();



    void on_pushButton_10_clicked(bool checked);

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::Board *ui;
};
extern int tool;
extern int tool_a;
extern int tool_b;
extern int tool_c;
extern int tool_d;
extern int tool_e;
extern int tool_f;
extern int tool_g;
extern int tool_z;
extern int tool_choose;
extern int num_color ;
extern int color;
extern int light;
#endif // BOARD_H
