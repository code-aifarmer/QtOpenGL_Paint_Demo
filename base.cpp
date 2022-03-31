#include "base.h"
#include "ui_base.h"
#include "ui_board.h"
#include "board.h"
#include "QMessageBox"
#include <QFileDialog>
#include "ui_openglwidget.h"
Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);
    resize(1031,579);
    setMaximumSize(1031,579);
    setMinimumSize(1031,579);
    QPixmap pixmap(":/new/prefix1/main.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));
        setPalette(palette);
        setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
        setAutoFillBackground(true);

        setWindowOpacity(0.8); //设置widget窗体透明度
        this->setWindowIcon(QIcon(":/new/prefix1/icon23.ico"));
        this->setWindowTitle("Painter");
}

Base::~Base()
{
    delete ui;
}


void Base::on_pushButton_clicked()
{
    this->hide();
    (new Board)->show();
}




