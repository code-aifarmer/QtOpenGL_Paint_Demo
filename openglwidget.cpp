#include "openglwidget.h"
#include "ui_openglwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "board.h"
#include "QPaintEvent"
#include "qDebug"
#include "math.h"
#include "QPainter"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
Openglwidget::Openglwidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::Openglwidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_Source);
     painter.fillRect(this->rect(), QColor(1, 1, 1, 1));
    //setWindowOpacity(1.0); 
     rotate_angle2 = 0.0;
}

Openglwidget::~Openglwidget()
{
    delete ui;
}

void Openglwidget::initializeGL()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth(1);
    glShadeModel(GL_SMOOTH);
    GLfloat _ambient[]={1.0,1.0,1.0,1.0};
    GLfloat _diffuse[]={1.0,1.0,0.0,1.0};
    GLfloat _specular[]={1.0,1.0,1.0,1.0};
    GLfloat _position[]={200,200,200,0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,_position);
    glEnable(GL_TEXTURE_3D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);




//    glClearColor(1,1,1,0);
        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_LIGHT0);
//        glEnable(GL_LIGHTING);
//        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//        glEnable(GL_COLOR_MATERIAL);

           glClearColor(1.0, 1.0, 1.0, 0.0);
          // glColor3f(0.0, 0.0, 0.0);

           //glPointSize(5.0);
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           glMatrixMode(GL_PROJECTION); 
           glLoadIdentity(); 
           gluOrtho2D(0.0, this->width(), 0.0, this->height());


}
GLvoid DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
    GLfloat vertex[4];

    const GLfloat delta_angle = 2.0*M_PI/num_segments;
    glBegin(GL_TRIANGLE_FAN);

    vertex[0] = cx;
    vertex[1] = cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);

    //draw the vertex on the contour of the circle
    for(int i = 0; i < num_segments ; i++)
    {
        vertex[0] = std::cos(delta_angle*i) * r + cx;
        vertex[1] = std::sin(delta_angle*i) * r + cy;
        vertex[2] = cz;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
    }

    vertex[0] = 1.0 * r + cx;
    vertex[1] = 0.0 * r + cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();
}
void RenderBone(float x0, float y0, float z0, float x1, float y1, float z1 )
{
    GLdouble  dir_x = x1 - x0;
    GLdouble  dir_y = y1 - y0;
    GLdouble  dir_z = z1 - z0;
    GLdouble  bone_length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
    static GLUquadricObj *  quad_obj = NULL;
    if ( quad_obj == NULL )
        quad_obj = gluNewQuadric();
    gluQuadricDrawStyle( quad_obj, GLU_FILL );
    gluQuadricNormals( quad_obj, GLU_SMOOTH );
    glPushMatrix();
    // 平移到起始点
    glTranslated( x0, y0, z0 );
    // 计算长度
    double  length;
    length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
    if ( length < 0.0001 ) {
        dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;
    }
    dir_x /= length;  dir_y /= length;  dir_z /= length;
    GLdouble  up_x, up_y, up_z;
    up_x = 0.0;
    up_y = 1.0;
    up_z = 0.0;
    double  side_x, side_y, side_z;
    side_x = up_y * dir_z - up_z * dir_y;
    side_y = up_z * dir_x - up_x * dir_z;
    side_z = up_x * dir_y - up_y * dir_x;
    length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );
    if ( length < 0.0001 ) {
        side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;
    }
    side_x /= length;  side_y /= length;  side_z /= length;
    up_x = dir_y * side_z - dir_z * side_y;
    up_y = dir_z * side_x - dir_x * side_z;
    up_z = dir_x * side_y - dir_y * side_x;
    // 计算变换矩阵
    GLdouble  m[16] = { side_x, side_y, side_z, 0.0,
        up_x,   up_y,   up_z,   0.0,
        dir_x,  dir_y,  dir_z,  0.0,
        0.0,    0.0,    0.0,    1.0 };
    glMultMatrixd( m );
    GLdouble radius= 0.1;		// 半径
    GLdouble slices = 10.0;		//	段数
    GLdouble stack = 3.0;		// 递归次数
    glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );// 正面接受环境光和散射光
    glEnable( GL_COLOR_MATERIAL );
    glColor3f(63.0/255.0, 72.0/255.0, 204.0/255.0);
    gluCylinder( quad_obj, radius, radius, bone_length, slices, stack );
    DrawCircleArea(0.0, 0.0, bone_length, radius, slices);
       //base
    DrawCircleArea(0.0, 0.0, 0.0, radius, slices);

    glPopMatrix();
}

void  Openglwidget::drawCube()
{
    glBegin(GL_QUAD_STRIP);          //填充凸多边形
    glColor3f( 1 ,  0 ,  0 );
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glColor3f( 1 ,  1 ,  0 );
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glColor3f( 0 ,  1 ,  0 );
    glVertex3f( 1.0f,  0.0f,  0.0f);
    glColor3f( 0 ,  1 ,  1 );
    glVertex3f( 1.0f,  1.0f,  0.0f);
    glColor3f( 1 ,  0 ,  0 );
    glVertex3f( 1.0f,  0.0f, - 1.0f);
    glColor3f( 1 ,  1 ,  0 );
    glVertex3f( 1.0f,  1.0f, - 1.0f);
    glColor3f( 0 ,  1 ,  0 );
    glVertex3f( 0.0f,  0.0f, - 1.0f);
    glColor3f( 0 ,  1 ,  1 );
    glVertex3f( 0.0f,  1.0f, - 1.0f);
    glColor3f( 1 ,  0 ,  0 );
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glColor3f( 1 ,  1 ,  0 );
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glColor3f( 0 ,  0 ,  1 );
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glColor3f( 1 ,  0 ,  1 );
    glVertex3f( 1.0f,  0.0f,  0.0f);
    glColor3f( 0 ,  1 ,  0 );
    glVertex3f( 0.0f,  0.0f, - 1.0f);
    glColor3f( 1 ,  0 ,  0 );
    glVertex3f( 1.0f,  0.0f, - 1.0f);
    glColor3f( 1 ,  1 ,  0 );
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glColor3f( 1 ,  0 ,  1 );
    glVertex3f( 1.0f,  1.0f,  0.0f);
    glColor3f( 0 ,  0 ,  1 );
    glVertex3f( 0.0f,  1.0f, - 1.0f);
    glColor3f( 1 ,  0 ,  0 );
    glVertex3f( 1.0f,  1.0f, - 1.0f);
    glEnd();
}

void Openglwidget::paintGL()
{   int i =0;

    if(light==1)
    {

        glGetIntegerv(GL_VIEWPORT, vt);   /* 获取三个矩阵 */
        glGetDoublev(GL_MODELVIEW_MATRIX, mx);
        glGetDoublev(GL_PROJECTION_MATRIX, pr);


      //px,py,pz
            qDebug()<<px<<" "<<py<<" "<<pz;
          GLfloat position[] = {(GLfloat)px, (GLfloat)py, (GLfloat)pz,0.0 };
          GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
           GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };

       glLightfv (GL_LIGHT0, GL_POSITION, position);
       glLightfv(GL_LIGHT0, GL_POSITION, position);
          glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   
          glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient); 

          glEnable(GL_LIGHTING);   
          glEnable(GL_LIGHT0);    
          glEnable(GL_DEPTH_TEST); 
    }


    glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );
//    qDebug()<<"!!!!"<<tool_a<<" "<<tool;
      glLoadIdentity();
      if(tool_a==1||vv.size()!=0){
          if(to_3d==1){
         glRotatef(rotate_angle2, 0.0,0.4, 0.0);
          }
      //  qDebug()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
   //     qDebug()<<tool_a<<" "<<vv.size();
      glPointSize(5.0);
       glLineWidth(2.0f);//线宽
      //glBegin(GL_POINTS);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glShadeModel(GL_FLAT);
      glBegin(GL_LINE_STRIP);
       // qDebug()<<"?????????????"<<color;
      for(i =0;i<vv.size();i++){
         // qDebug() << i << " " << vv[i].flag;
          if(i > 1 && vv[i - 1].flag) {
//              glColor3f(1.0,1.0,1.0);
              glEnd();
              glShadeModel(GL_FLAT);
              glBegin(GL_LINE_STRIP);
              //glVertex2d(vv[i].x, vv[i].y);

//              glColor3f(0.9,0.5,0.0);
             // qDebug()<<color<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
              if(color==0){
              glColor3f(0.9,0.5,0.0);//橙色
              color_flag = 0;
              }
              else if(color==1)
              {
                glColor3f(0.4,0.7,0.3);//绿
                color_flag = 1;
              }
              else if(color==2)
              {
                glColor3f(0.8,0.5,0.7);//紫
                color_flag = 2;
              }
              else if(color==3)
              {
                glColor3f(0.9,0.2,0.2);//red
                color_flag = 3;
              }
              else if(color==4)
              {
                glColor3f(0.1,0.7,0.7);//浅蓝
                color_flag = 4;
              }
              else
              {
                glColor3f(0.0,0.0,0.0);//黑
                color_flag = 5;
              }
          }
          else
          {
              if(vv[i].c_flag==0){
                   glColor3f(0.9,0.5,0.0);//橙色
                   glVertex2d(vv[i].x, vv[i].y);

              }
              else if(vv[i].c_flag==1){
                   glColor3f(0.4,0.7,0.3);//绿
                   glVertex2d(vv[i].x, vv[i].y);

              }
              else if(vv[i].c_flag==2){
                    glColor3f(0.8,0.5,0.7);//紫
                   glVertex2d(vv[i].x, vv[i].y);

              }
              else if(vv[i].c_flag==3){
                  glColor3f(0.9,0.2,0.2);//red
                   glVertex2d(vv[i].x, vv[i].y);

              }
              else if(vv[i].c_flag==4){
                  glColor3f(0.1,0.7,0.7);//浅蓝
                   glVertex2d(vv[i].x, vv[i].y);

              }
              else
              {
                 glColor3f(0.0,0.0,0.0);//黑
                   glVertex2d(vv[i].x, vv[i].y);
              }



          }
      //qDebug()<<vv[i].x<<" "<<vv[i].y<<"!!!"<<endl;
      }
      //qDebug()<<"???????????"<<vv.size();

      //qDebug()<<num_point<<endl;


        glEnd();
      }
      if(tool_b==1||vvv.size()!=0){
          glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
          glEnable( GL_COLOR_MATERIAL );
          if(to_3d==1){
         glRotatef(rotate_angle2, 0.0,0.4, 0.0);
          }
      //  qDebug()<<"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
      glPointSize(5.0);
       glLineWidth(2.0f);//线宽
      glBegin(GL_POINTS);
   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glShadeModel(GL_FLAT);
    //  glBegin(GL_LINE_STRIP);
      //glBegin(GL_LINE_LOOP);
      //glColor3f(0.9,0.5,0.0);
      //glVertex2d(0.0, 0.0);
      //qDebug() << "STATODA" << Qt::endl;
      for(i =0;i<vvv.size();i++){
         // qDebug() << i << " " << vv[i].flag;
          if(i > 1 && vvv[i - 1].flag) {
              glColor3f(1.0,1.0,1.0);
              glVertex2d(vvv[i].x, vvv[i].y);
             // glColor3f(0.9,0.5,0.0);
              if(color==0){
              glColor3f(0.9,0.5,0.0);//橙色
              color_flag = 0;
              }
              else if(color==1)
              {
                glColor3f(0.4,0.7,0.3);//绿
                color_flag = 1;
              }
              else if(color==2)
              {
                glColor3f(0.8,0.5,0.7);//紫
                color_flag = 2;
              }
              else if(color==3)
              {
                glColor3f(0.9,0.2,0.2);//red
                color_flag = 3;
              }
              else if(color==4)
              {
                glColor3f(0.1,0.7,0.7);//浅蓝
                color_flag = 4;
              }
              else
              {
                glColor3f(0.0,0.0,0.0);//黑
                color_flag = 5;
              }
          }
          else
          {
              if(vvv[i].c_flag==0){
                   glColor3f(0.9,0.5,0.0);//橙色
                   glVertex2d(vvv[i].x, vvv[i].y);

              }
              else if(vvv[i].c_flag==1){
                   glColor3f(0.4,0.7,0.3);//绿
                   glVertex2d(vvv[i].x, vvv[i].y);

              }
              else if(vvv[i].c_flag==2){
                    glColor3f(0.8,0.5,0.7);//紫
                   glVertex2d(vvv[i].x, vvv[i].y);

              }
              else if(vvv[i].c_flag==3){
                  glColor3f(0.9,0.2,0.2);//red
                   glVertex2d(vvv[i].x, vvv[i].y);

              }
              else if(vvv[i].c_flag==4){
                  glColor3f(0.1,0.7,0.7);//浅蓝
                   glVertex2d(vvv[i].x, vvv[i].y);

              }
              else
              {
                 glColor3f(0.0,0.0,0.0);//黑
                   glVertex2d(vvv[i].x, vvv[i].y);
              }



          }
      //qDebug()<<vv[i].x<<" "<<vv[i].y<<"!!!"<<endl;
      }
      //qDebug()<<"???????????"<<vv.size();

      //qDebug()<<num_point<<endl;


        glEnd();
      }
      if(tool_c==1||vvvv.size()!=0){
          glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );// 这个表示模型的正面接受环境光和散射光，你可以修改这两个参数
          glEnable( GL_COLOR_MATERIAL );
          if(to_3d==1){
         glRotatef(rotate_angle2, 0.0,0.4, 0.0);
          }
          glPointSize(10.0);
        glLineWidth(10.0f);//线宽
     // glBegin(GL_POINTS);
      //glClear(GL_DEPTH_BUFFER_BIT);
      //  glClear(GL_COLOR_BUFFER_BIT );
//      glShadeModel(GL_FLAT);
      glBegin(GL_LINE_STRIP);
      //glBegin(GL_LINE_LOOP);
      //glColor3f(0.9,0.5,0.0);
      //glVertex2d(0.0, 0.0);
     // qDebug() << "STATODA" << Qt::endl;
      for(i =0;i<vvvv.size();i++){
        //  qDebug() << i << " " << vvvv[i].flag;
          if(i > 1 && vvvv[i - 1].flag) {
              //glLineWidth(10.0f);//线宽
//              glColor3f(1.0,1.0,1.0);
//              glVertex2d(vvvv[i].x, vvvv[i].y);
              glEnd();
               glBegin(GL_LINE_STRIP);
              //glColor3f(0.9,0.5,0.0);
             // qDebug()<<"?????????????"<<color;
              if(color==0){
              glColor3f(0.9,0.5,0.0);//橙色
              color_flag = 0;
              }
              else if(color==1)
              {
                glColor3f(0.4,0.7,0.3);//绿
                color_flag = 1;
              }
              else if(color==2)
              {
                glColor3f(0.8,0.5,0.7);//紫
                color_flag = 2;
              }
              else if(color==3)
              {
                glColor3f(0.9,0.2,0.2);//red
                color_flag = 3;
              }
              else if(color==4)
              {
                glColor3f(0.1,0.7,0.7);//浅蓝
                color_flag = 4;
              }
              else
              {
                glColor3f(0.0,0.0,0.0);//黑
                color_flag = 5;
              }
          }
          else
          {
              if(vvvv[i].c_flag==0){
                   glColor3f(0.9,0.5,0.0);//橙色
                   glVertex2d(vvvv[i].x, vvvv[i].y);

              }
              else if(vvvv[i].c_flag==1){
                   glColor3f(0.4,0.7,0.3);//绿
                   glVertex2d(vvvv[i].x, vvvv[i].y);

              }
              else if(vvvv[i].c_flag==2){
                    glColor3f(0.8,0.5,0.7);//紫
                   glVertex2d(vvvv[i].x, vvvv[i].y);

              }
              else if(vvvv[i].c_flag==3){
                  glColor3f(0.9,0.2,0.2);//red
                   glVertex2d(vvvv[i].x, vvvv[i].y);

              }
              else if(vvvv[i].c_flag==4){
                  glColor3f(0.1,0.7,0.7);//浅蓝
                   glVertex2d(vvvv[i].x, vvvv[i].y);

              }
              else
              {
                 glColor3f(0.0,0.0,0.0);//黑
                   glVertex2d(vvvv[i].x, vvvv[i].y);
              }



          }
      //qDebug()<<vv[i].x<<" "<<vv[i].y<<"!!!"<<endl;
      }
      //qDebug()<<"???????????"<<vv.size();

      //qDebug()<<num_point<<endl;


        glEnd();
      }

if(tool_d==1)
{  glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );
    if(to_3d==1){
   glRotatef(rotate_angle2, 0.0,0.4, 0.0);
    }
     glPointSize(5.0);glLineWidth(4.0f);//线宽
     glColor3f(0.8,0.5,0.7);//紫
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     if(clear_bei==1)
//     {   bei_num=0;
//         clear_bei = 0;
//     }
     for(int i =0;i<bei_num;i++)
     {
         glBegin(GL_POINTS);
        glColor3f(0.9,0.5,0.0);
          glVertex2d(pp[i].x, pp[i].y);
          glEnd();
     }

     for(int i =0;i+1<bei_num;i++)
     {
        // glClear(GL_COLOR_BUFFER_BIT );

         glBegin(GL_LINES);

         glVertex2d(pp[i].x, pp[i].y);
         glVertex2d(pp[i+1].x, pp[i+1].y);
            glEnd();
     }

        glColor3f(1.0, 0.8, 0.2);
        p1 =pp[0];
        if(bei_num%4==0&&bei_num>=4){
        for(double t = 0.0;t<=1.0;t+=0.05)
        {
            double a1 = pow((1 - t), 3);
            double a2 = pow((1 - t), 2) * 3 * t;
            double a3 = 3 * t * t * (1 - t);
            double a4 = t * t * t;
            p2.x = a1 * pp[0].x + a2 * pp[1].x + a3 * pp[2].x + a4 * pp[3].x;
            p2.y = a1 * pp[0].y + a2 * pp[1].y + a3 * pp[2].y + a4 * pp[3].y;
            //glLineWidth(4.0f);//线宽
            glBegin(GL_LINES);
             glColor3f(0.9,0.2,0.2);//
            glVertex2d(p1.x, p1.y);
            glVertex2d(p2.x, p2.y);
            glEnd();
            p1 = p2;
        }
        }





}
static const GLfloat vertex_list[][3] = {
{-0.5f, -0.5f, -0.5f},
{0.5f, -0.5f, -0.5f},
{-0.5f, 0.5f, -0.5f},
{0.5f, 0.5f, -0.5f},
{-0.5f, -0.5f, 0.5f},
{0.5f, -0.5f, 0.5f},
{-0.5f, 0.5f, 0.5f},
{0.5f, 0.5f, 0.5f},
};
static const GLint index_list[][4] = {
{0, 2, 3, 1},
{0, 4, 6, 2},
{0, 1, 5, 4},
{4, 5, 7, 6},
{1, 3, 7, 5},
{2, 6, 7, 3},
};

if(tool_e==1)
{


    //glLoadIdentity();
    glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );// 这个表示模型的正面接受环境光和散射光，你可以修改这两个参数
    glEnable( GL_COLOR_MATERIAL );
       glTranslated(0.5, 0, 0.5);//将绘制平面移动到屏幕的右半平面和外面
     gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f);
       glRotatef(rotate_angle2, -0.5, 0.2, -0.3);

       //glBegin(GL_QUADS);

        glBegin(GL_POLYGON );
       //上顶面

//      glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(-0.3, 0.3, -0.3);
   glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(-0.3, 0.3, 0.3);
     glColor3f(0.0, 0.0, 1.0);//蓝

       glVertex3f(0.3, 0.3, 0.3);
     glColor3f(0.0, 1.0, 0.0);//绿

       glVertex3f(0.3, 0.3, -0.3);

       //下顶面

//      glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(-0.3, -0.3, -0.3);
 glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(-0.3, -0.3, 0.3);
 glColor3f(0.0, 0.0, 1.0);//蓝
       glVertex3f(0.3, -0.3, 0.3);
 glColor3f(0.0, 1.0, 0.0);//绿
       glVertex3f(0.3, -0.3, -0.3);

       //正前面

//      glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(-0.3, 0.3, 0.3);
 glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(-0.3, -0.3, 0.3);
 glColor3f(0.0, 0.0, 1.0);//蓝
       glVertex3f(0.3, -0.3, 0.3);
 glColor3f(0.0, 1.0, 0.0);//绿
       glVertex3f(0.3, 0.3, 0.3);

       //右侧面

//     glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(0.3, 0.3, 0.3);
 glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(0.3, -0.3, 0.3);
 glColor3f(0.0, 0.0, 1.0);//蓝
       glVertex3f(0.3, -0.3, -0.3);
 glColor3f(0.0, 1.0, 0.0);//绿
       glVertex3f(0.3, 0.3, -0.3);

       //背后面

//   glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(-0.3, 0.3, -0.3);
       glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(0.3, 0.3, -0.3);
 glColor3f(0.0, 0.0, 1.0);//蓝
       glVertex3f(0.3, -0.3, -0.3);
 glColor3f(0.0, 1.0, 0.0);//绿
       glVertex3f(-0.3, -0.3, -0.3);

       //左侧面

//     glColor3f(0.9,0.5,0.0);//橙色

       glVertex3f(-0.3, 0.3, -0.3);
 glColor3f(1.0, 0.0, 0.0);//红
       glVertex3f(-0.3, -0.3, -0.3);
 glColor3f(0.0, 0.0, 1.0);//蓝
       glVertex3f(-0.3, -0.3, 0.3);
 glColor3f(0.0, 1.0, 0.0);//绿
       glVertex3f(-0.3, 0.3, 0.3);

//       rotate_angle2 -= 3;

   glEnd();

}
    if(erase==1){
//      //  qDebug()<<"EEEEEEEEEEEEEEEEEEEEE";


      glLoadIdentity();

      float iii = -(erase_start_y/((this->width())*2-1));
      float  ii = -(erase_start_x/-((this->height())*2-1));
      float j = erase_start_x+1;
      float jj = erase_start_y+1;
      int n = 0;
//      while(iii<j&&ii<jj)
//      {
//          while(ii<jj)
//          {

//              glVertex2d(ii,iii+10);
//              glVertex2d(ii,iii+10);
//              ii=ii+0.01;
//              qDebug()<<n++;
//          }
//          iii = iii+0.01;

//      }
          glBegin(GL_POLYGON);glColor3f(0.0,0.0,0.0);
              glVertex3f(ii, iii, 0.0f); // 左上顶点
              glVertex3f(ii+0.05, iii, 0.0f); // 右上顶点
              glVertex3f( ii+0.05, iii+0.05, 0.0f); // 右下顶点
              glVertex3f(ii, iii+0.05, 0.0f); // 左下顶点
               // 四边形绘制结束
//      qDebug()<<"out";
              glEnd();

    }
    if(tool_z==1||z.size()!=0)
    {//glColor3f(0.9,0.2,0.2);//red
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glShadeModel(GL_SMOOTH);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

//        glLoadIdentity();
//
      glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );// 这个表示模型的正面接受环境光和散射光，你可以修改这两个参数
      glEnable( GL_COLOR_MATERIAL );
//        glLoadIdentity();
        //gluLookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(rotate_angle2, -0.3, 0.2, -0.1);
        glScaled(0.5,0.5,0.5);
        glGetIntegerv(GL_VIEWPORT, viewport);   /* 获取三个矩阵 */
        glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

//        for(int i = 0;i<4;i++)
//        {


//            qDebug()<<mvmatrix[i*4]<<" "<<mvmatrix[i*4+1]<<" "<<mvmatrix[i*4+2]<<" "<<mvmatrix[i*4+3];
//        }





//        glLineWidth(4.0f);
//        glBegin(GL_LINES);
//        glColor3f(0.9,0.2,0.2);//red
//        glVertex3d(0, 0,0);
//        glVertex3d(0,0,1);
//        glColor3f(0.2,0.9,0.2);//green
//        glVertex3d(0,0,0);
//        glVertex3d(0,1,0);
//        glColor3f(0.2,0.2,0.9);//blue
//        glVertex3d(0,0,0);
//        glVertex3d(1,0,0);
//           glEnd();
        /*坐标轴*/

//        glShadeModel(GL_FLAT);
//        glBegin(GL_LINES);
//        glColor3f(0.9,0.2,0.2);//red
//          for(int i =0;i+1<z.size();i++){
//          glVertex3f(z[i].x,z[i].y,z[i].z);
//          glVertex3f(z[i+1].x,z[i].y,z[i].z);
//          }

//          glEnd();
//glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
              //bottom circle
           glColor3f(0.2,0.2,0.9);

          for(int i =0;i+1<z.size();i++){
         //  qDebug() << i << " " << z[i].flag;
              if(z[i].flag==true){
                  continue;

              }

              glMatrixMode(GL_MODELVIEW);
//              glLoadIdentity();

              glPushMatrix();
              {
                  RenderBone(z[i].x, z[i].y,z[i].z, z[i+1].x, z[i+1].y, z[i+1].z);


              } glPopMatrix();
              update();

}

//          glPointSize(5.0);
//          glBegin(GL_POINTS);
//         // glShadeModel(GL_FLAT);
//          glColor3f(0.9,0.2,0.2);//red

//          //glVertex3f(0.3,0.3,0.3);
//          glVertex3d(posx,posy,posz);
//          qDebug()<<"//////"<<posx<<" "<<posy<<" "<<posz;

//          glEnd();

//          glBegin(GL_POINTS);
//          glColor3f(0.9,0.2,0.2);//red
//          glPointSize(5.0);

//          glVertex3i(-2,2,2);
//          glEnd();
    }


}
void Openglwidget::wheelEvent(QWheelEvent *ev)
{

    QPoint numPixels = ev->pixelDelta();
        QPoint numDegrees = ev->angleDelta();
        int delta = ev->delta ();
//        qDebug() << "numPixels:"<<numPixels;
//        qDebug() << "numDegrees:"<<numDegrees;
//        qDebug() << "delta:"<<delta;
//        qDebug() << "the wheel event source: "<<event->source ();
        if(numDegrees.y()>0){
             rotate_angle2 -= 2;
        }else{
             rotate_angle2+= 2;
        }


}
void Openglwidget::mousePressEvent(QMouseEvent *ev)
{
//    if(ev->button()==Qt::MiddleButton)


    if(clear_bei==1)
    {
        num_point_bei = 0;
        bei_num = 0;
        clear_bei = 0;

    }
    if(ev->button()==Qt::LeftButton&&jud==0)
    {
        jud = 1;
        erase = 0;
        pp[num_point_bei].x=((float)ev->pos().x()/(this->width()))*2-1;
        pp[num_point_bei].y=-((((float)ev->pos().y())/(this->height()))*2-1);
        num_point_bei++;
        bei_num++;


    }

    else if(ev->button()==Qt::RightButton&&erase!=1)
    {
        erase = 1;
        jud =0;
        pp[num_point_bei].x=((float)ev->pos().x()/(this->width()))*2-1;
        pp[num_point_bei].y=-((((float)ev->pos().y())/(this->height()))*2-1);
        num_point_bei++;
        bei_num++;

        //z.push_back({posx,posy,posz});
    }
    else
    {
        jud  =0;
        erase = 0;
        if(tool_a==1)
  /**/  vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), true});
        if(tool_b==1)
  /**/  vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), true});
        if(tool_c==1)
  /**/  vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), true});
        pp[num_point_bei].x=((float)ev->pos().x()/(this->width()))*2-1;
        pp[num_point_bei].y=-((((float)ev->pos().y())/(this->height()))*2-1);

        num_point_bei++;
        bei_num++;
        if(tool_z==1)
        z.push_back({posx,posy,posz,true});

           // z.push_back({posx,posy,posz});
       // qDebug()<<jud;
    }
}
void Openglwidget::mouseMoveEvent(QMouseEvent *ev)
{

    if(light==1)
    {
        int light_x = ev->pos().x();    /* 屏幕坐标 */
        int light_y = ev->pos().y();

        GLfloat wx, wy, wz;
        wx = light_x;
        wy = this->height() - light_y;

        gluUnProject(wx, wy, 0.5, mx, pr, vt, &px, &py, &pz); /* 获取三维坐标 */
    }
    if(jud==1&&tool_choose==1){

        if(tool_a==1){
         //   qDebug()<<"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS";
        if(color==0)
        {
        vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,0});
        }
        else if(color==1)
        {
             vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,1});
        }
        else if(color==2)
        {
             vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,2});
        }
        else if(color==3)
        {
             vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,3});
        }
        else if(color==4)
        {
             vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,4});
        }
        else if(color==5)
        {
             vv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,5});
        }


        }
        if(tool_b==1)
        {
            if(color==0)
            {
            vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,0});
            }
            else if(color==1)
            {
                 vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,1});
            }
            else if(color==2)
            {
                 vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,2});
            }
            else if(color==3)
            {
                 vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,3});
            }
            else if(color==4)
            {
                 vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,4});
            }
            else if(color==5)
            {
                 vvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,5});
            }
        }
        if(tool_c==1)
        {
            if(color==0)
            {
            vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,0});
            }
            else if(color==1)
            {
                 vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,1});
            }
            else if(color==2)
            {
                 vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,2});
            }
            else if(color==3)
            {
                 vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,3});
            }
            else if(color==4)
            {
                 vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,4});
            }
            else if(color==5)
            {
                 vvvv.push_back({((float)ev->pos().x()/(this->width()))*2-1,-((((float)ev->pos().y())/(this->height()))*2-1), false,5});
            }
        }
        if(tool_z==1)
        {


        int x = ev->pos().x();    /* 屏幕坐标 */
        int y = ev->pos().y();

        GLfloat winx, winy, winz;
        winx = x;
        winy = this->height() - y;

        gluUnProject(winx, winy, 0.5, mvmatrix, projmatrix, viewport, &posx, &posy, &posz); /* 获取三维坐标 */
        z.push_back({posx,posy,posz,false});


        }

    }

    if(erase == 1)
    {
        erase_start_x =(float)ev->pos().x();
        erase_start_y =(float)ev->pos().y();
//        for(float i = ev->pos().x()-10;i<ev->pos().x()+10;i+=0.01)
//        {
//            for(float j = ev->pos().y()-10;j<ev->pos().y()+10;j+=0.01)
//            {
//                ea[ev->pos().x()][ev->pos().y()] = 1;
//            }
//        }

    }
    update();


}
void Openglwidget::mouseReleaseEvent(QMouseEvent *ev)
{

}
void Openglwidget::resizeGL(int w,int h)
{

    glEnable(GL_DEPTH_TEST);    //深度测试
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00); // 保证绘制其他物品的时候不会更新模板缓冲

    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式
       // GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0
        GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光
        GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
      //  glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

//        //开启灯光
//        glEnable(GL_LIGHT0);
//        glEnable(GL_LIGHTING);
//        glEnable(GL_DEPTH_TEST);


       //glViewport(0,0,w,h);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(45, (float)w/h, 0.01, 100.0);

       //glMatrixMode(GL_MODELVIEW);
     //  glLoadIdentity();
     //  gluLookAt(20.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f, 0.0f);



}

