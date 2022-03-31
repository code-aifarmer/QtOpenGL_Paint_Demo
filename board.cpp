#include "board.h"
#include "ui_board.h"
#include "qDebug"
#include "openglwidget.h"
#include <QFileDialog>
#include "QScreen"
#include "QMessageBox"
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
Board::Board(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Board)
{
      ui->setupUi(this);
      ui->pushButton->setCheckable(true);
      ui->pushButton_2->setCheckable(true);
      ui->pushButton_3->setCheckable(true);
      ui->pushButton_4->setCheckable(true);
      ui->pushButton_5->setCheckable(true);
      ui->pushButton_6->setCheckable(true);
      ui->pushButton_7->setCheckable(true);
      ui->pushButton_10->setCheckable(true);
//      ui->pushButton_9->setAutoFillBackground(true);
//      QPalette a = ui->pushButton_9->palette();
       ui->pushButton_9->setStyleSheet("background-color: #FB8B05;");
      qDebug()<<"&&&&&&&&&&&&&"<<color;

//      if(color==0)
//      {

//          ui->pushButton_9->setStyleSheet("background-color: #FB8B05;");
//      }
//      else if(color==1)
//      {
//           ui->pushButton_9->setStyleSheet("background-color: #05FB90;");
//      }
//      else if(color==2)
//      {
//          ui->pushButton_9->setStyleSheet("background-color: #A505FB;");
//      }
//      else if(color==3)
//      {
//          ui->pushButton_9->setStyleSheet("background-color: #FB0509;");
//      }
//      else if(color==4)
//      {
//          ui->pushButton_9->setStyleSheet("background-color: #05DAFB;");
//      }
//      else if(color==5)
//      {
//           ui->pushButton_9->setStyleSheet("background-color: #000000;");
//      }
      QPalette palette;
       QPixmap pixmap(":/new/prefix1/main.jpg");
      palette.setBrush(this->backgroundRole(),QBrush(pixmap));
          setPalette(palette);
          setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
          setAutoFillBackground(true);

          setWindowOpacity(1.0); //设置widget窗体透明度
          this->setWindowIcon(QIcon(":/new/prefix1/icon23.ico"));
          this->setWindowTitle("Painter");

        //ui->pushButton_9->setPalette(a);
//    ui->widget->show();



}
void Board:: change_color()
{
    if(color==0)
    {

        ui->pushButton_9->setStyleSheet("background-color: #FB8B05;");
    }
    else if(color==1)
    {
         ui->pushButton_9->setStyleSheet("background-color: #05FB90;");
    }
    else if(color==2)
    {
        ui->pushButton_9->setStyleSheet("background-color: #A505FB;");
    }
    else if(color==3)
    {
        ui->pushButton_9->setStyleSheet("background-color: #FB0509;");
    }
    else if(color==4)
    {
        ui->pushButton_9->setStyleSheet("background-color: #05DAFB;");
    }
    else if(color==5)
    {
         ui->pushButton_9->setStyleSheet("background-color: #000000;");
    }
}
Board::~Board()
{
    delete ui;
}

void Board::on_pushButton_clicked(bool checked)//铅笔
{
    to_3d = 0;
    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_a = 1;
        //tool=0;
        tool_choose = 1;
        qDebug()<<"TOOL_A:"<<tool_a<<" "<<tool;
    }
    else
    {
        tool_a = 0;
        tool=1;
        qDebug()<<"N";
    }
}


void Board::on_pushButton_2_clicked(bool checked)//点绘
{
    to_3d = 0;
    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_b = 1;
        tool_choose = 1;
        //tool=0;
    }
    else
    {
        qDebug()<<"N";
        tool_b = 0;
        tool = 1;
    }
}


void Board::on_pushButton_3_clicked(bool checked)//涂鸦
{
    to_3d = 0;
    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_c = 1;
        tool_choose = 1;
        //tool  =0;
    }
    else
    {
        qDebug()<<"N";
        tool_c = 0;
        tool =1;
    }
}


void Board::on_pushButton_4_clicked(bool checked)//贝塞尔
{
    to_3d = 0;
    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_d = 1;
        tool_choose = 1;
        //tool = 0;
    }
    else
    {
        qDebug()<<"N";
        tool_d = 0;
        tool = 1;
    }
}


void Board::on_pushButton_5_clicked(bool checked)
{
    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_e = 1;
        tool_choose = 1;
        //tool  =0;
    }
    else
    {
        qDebug()<<"N";
        tool_e = 0;
        tool  =1;
    }
}


void Board::on_pushButton_6_clicked(bool checked)
{
    if(checked&&tool==1)
    {

       to_3d = 1;


    }
    else
    {
        to_3d= 0;
    }


}


void Board::on_pushButton_7_clicked(bool checked)
{
    if(checked&&tool==1)
    {

      light = 1;
    }
    else
    {
       light = 0;
    }
}


void Board::on_pushButton_8_clicked()
{
    vv.clear();
    vvv.clear();
    vvvv.clear();
    clear_bei=1;
    z.clear();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Board::on_pushButton_9_clicked()
{
    qDebug()<<num_color<<"@@@"<<endl;
    num_color++;
    if(num_color==0)
    {
        //ui->pushButton_9->setText("橙色");
        color = 0;


    }
    else if(num_color==1)
    {
      // ui->pushButton_9->setText("绿色");
       color = 1;
    }
    else if(num_color==2)
    {
    //   ui->pushButton_9->setText("紫色");
       color = 2;
    }
    else if(num_color==3)
    {
     //  ui->pushButton_9->setText("红色");
       color  = 3;
    }
    else if(num_color==4)
    {
      // ui->pushButton_9->setText("浅蓝色");
       color = 4;
    }
    else if(num_color==5)
    {
      // ui->pushButton_9->setText("黑色");
       color = 5;
    } 
    else
    {
        num_color=0;
        color = 0;
       // ui->pushButton_9->setText("橙色");
    }

    change_color();
}



void Board::on_pushButton_10_clicked(bool checked)
{
    qDebug()<<"ininininini"<<tool;

    if(checked&&tool==1)
    {

        qDebug()<<"Y";
        tool_z = 1;
        //tool=0;
        tool_choose = 1;
        qDebug()<<"TOOL_A:"<<tool_z<<" "<<tool;
    }
    else
    {
        tool_z = 0;
        tool=1;
        qDebug()<<"N";
    }
}


void Board::on_pushButton_12_clicked()
{
      QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
       QScreen *screen = QGuiApplication::primaryScreen();
       screen->grabWindow(ui->widget->winId()).save(filename1);
       QMessageBox::about(NULL,"提示","图片保存成功!");

}


void Board::on_pushButton_6_clicked()
{
    //to_3d= 1;
}


void Board::on_pushButton_11_clicked()
{
     QMessageBox::about(NULL,"提示","使用此功能请先开通VIP服务!");

}

