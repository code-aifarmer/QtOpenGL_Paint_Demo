#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include "QOpenGLWidget"
#include "QGLWidget"
#include <GL/gl.h>
#include <QVector>
#include <GL/glu.h>
#include "QKeyEvent"

namespace Ui {
class Openglwidget;
}
class v//坐标
{
public:
    float x;
    float y;
    /**
     * @brief flag if it's the end o a sort of points
     */
    bool flag;
    int c_flag;
    //int color_flag = 0;

    v(){}
    v(float x, float y) {
        this->x = x, this->y = y;
    }
    v(float x, float y, bool flag) {
        this->x = x, this->y = y;
        this->flag = flag;
    }
    v(float x, float y, bool flag,int c) {
        this->x = x, this->y = y;
        this->flag = flag;
        this->c_flag   =c;
    }
};
/**
 * @brief The zhu class
 * @author -皿-
 */
class zhu
{
public:
    GLdouble x;
    GLdouble y;
    GLdouble z;
    bool flag;

    zhu(GLdouble x,GLdouble y,GLdouble z,bool flag)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->flag = flag;
    }
};

class point
{
public:
    double x;
    double y;
    void setpoint(double xx,double yy)
    {
        x = xx;
        y = yy;
    }
};
static int num_p = 0;
static point points[4];
static point select1;

extern point p1;//p_current
extern point p2;//P
extern point pp[1000];//points
//v k[1000];
//QVector<v>vv;
class Openglwidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Openglwidget(QWidget *parent = nullptr);
    ~Openglwidget();
    QPoint deltaPos;
    QPoint lastPos;
    QPoint currentPos;
    float light_x;
    float light_y;
    //void save();
    QVector<QVector<int>> ea;
    bool PressFlag = false;
    int  rotate_angle2;
    float Zyot;
    GLuint texture[1];
    void loadGLTextures();
private:
    Ui::Openglwidget *ui;
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    //void paintGL();
    void paintGL();
    void display();
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *event);
    void draw(v v1);
public slots:
    void drawCube();
    //void loadGLTextures();
};

extern int jud;
extern int num_point;
extern int erase;
extern float erase_start_x;
extern float erase_start_y;
extern int long_press;
extern QVector<v>vv;//铅笔
extern QVector<point>bb;
extern QVector<v>vvv;//点绘
extern QVector<v>vvvv;//涂鸦
extern int num_point_bei;
extern int bei_num;
extern int clear_bei;
extern int color_flag;
extern QVector<zhu>z;
extern GLdouble posx, posy, posz;
extern GLint viewport[4];
extern GLdouble mvmatrix[16], projmatrix[16];
extern int to_3d;
extern GLdouble px, py, pz;
extern GLint vt[4];
extern GLdouble mx[16], pr[16];
/**
 * @brief lbtnd left botton down
 */
extern bool lbtnd;
#endif // OPENGLWIDGET_H

