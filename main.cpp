#include "base.h"
#include "openglwidget.h"

#include <QApplication>
int jud = 0;

int num_point = 0;
int erase = 0;
float erase_start_x = 0.0;
float erase_start_y = 0.0;
int tool = 1;
int tool_a = 0;
int tool_b = 0;
int tool_c = 0;
int tool_d = 0;
int tool_e = 0;
int tool_f = 0;
int tool_g = 0;
int tool_choose = 0;
int long_press = 0;
int num_color = 0;
bool lbtnd = true;
int color = 0;
int num_point_bei = 0;
point p1;
point p2;
point pp[1000];
bool left_btn_down = 1;
int bei_num = 0;
int clear_bei = 0;
int color_flag=0;
int tool_z = 0;
GLdouble posx=0.0, posy=0.0, posz=0.0;
QVector<v>vv;//铅笔
QVector<v>vvv;//点绘
QVector<v>vvvv;//涂鸦
QVector<zhu>z;
GLint viewport[4];
GLdouble mvmatrix[16], projmatrix[16];
int to_3d = 0;
int light = 0;
GLdouble px, py, pz;
GLint vt[4];
GLdouble mx[16], pr[16];
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Base w;
    w.show();
    return a.exec();
}
