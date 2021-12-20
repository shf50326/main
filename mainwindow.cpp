#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QApplication>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QLabel>
#include <string>
#include <iostream>
using namespace std;
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTranslator>
#include <QDebug>
#include <QPaintDevice>
#include <QPainter>
#include <QImage>
#include <QtCore/qmath.h>
#include <QTimer>
#include<QDateTime>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    setWindowTitle("孙海烽 199050326");
    ui->Slider->setMinimum(0);//设置最小值
    ui->Slider->setMaximum(255);//设置最大值
    ui->Slider->setSingleStep(1);//设置每次移动更改的值
    ui->Slider->setValue(0);//设置初始值



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        QString filename=QFileDialog::getOpenFileName(this,tr("openfile"), "/","图片文件(*.png)");
        QImage s(filename);
        ui->label->setPixmap(QPixmap::fromImage(s));
        const QPixmap *img = ui->label->pixmap();
             abc=img->toImage();

}

void MainWindow::on_actionopen_triggered()
{
   QString filename=QFileDialog::getOpenFileName(this,tr("openfile"), "/","图片文件(*.png)");
   QImage s(filename);
   ui->label->setPixmap(QPixmap::fromImage(s));
   const QPixmap *img = ui->label->pixmap();
        abc=img->toImage();
}


void MainWindow::on_pushButton_2_clicked()
{
    const QPixmap *current_img = ui->label->pixmap();
    QString path="D:/qtdocument/shf-5/images";
    QString time = QDateTime::currentDateTime( ).toString("yyyy__A_dd_hh_mm_ss");
    current_img->save(QString("%1/%2.png").arg(path,time));

}

void MainWindow::on_pushButton_3_clicked()
{
    QTranslator translator;
    translator.load("../shf-5/shf-5_CN.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

}

void MainWindow::on_pushButton_4_clicked()
{
    QTranslator translator;
    translator.load("../shf-5/shf-5_EN.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString Brightvalue=ui->lineEdit->text();
    if(Brightvalue==""){
        QMessageBox::warning(this, tr("Waring"),
                             tr("请先输入相关的值"),
                             QMessageBox::Yes);
    }else{
    const QPixmap *img = ui->label->pixmap();
    QImage Img=img->toImage();
    int iBrightvalue=Brightvalue.toInt();
    int red,green,blue;
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int*)Img.bits();
    for (int i = 0; i < pixels; ++i)
    {
    red= qRed(data[i])+ iBrightvalue;
    red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;green= qGreen(data[i]) + iBrightvalue;
    green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;blue= qBlue(data[i]) + iBrightvalue;
    blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue ;data[i] = qRgba(red,green,blue,qAlpha(data[i]));
    }
    ui->label->setPixmap(QPixmap::fromImage(Img));
}

}

void MainWindow::on_pushButton_7_clicked()
{    const QPixmap *img = ui->label->pixmap();
     QImage image=img->toImage();
    QImage* newImage = new QImage(image.width(),image.height(),QImage::Format_ARGB32);
       QColor color0;
       QColor color1;
       QColor color2;
       QColor color3;
       QColor color4;
       QColor color5;
       QColor color6;
       QColor color7;
       QColor color8;
       int type=0;
       double scale=1;
       int  r = 0;
       int g = 0;
       int b = 0;
       int rgb = 0;
       int r1 = 0;
       int g1 = 0;
       int b1 = 0;
       int rgb1 = 0;
       int a = 0;
       for( int y = 1; y < image.height() - 1; y++)
       {
           for(int x = 1; x < image.width() - 1; x++)
           {
               color0 =   QColor ( image.pixel(x,y));

               color1=   QColor ( image.pixel(x-1,y-1));
               color2 =   QColor ( image.pixel(x,y-1));
               color3 =   QColor ( image.pixel(x+1,y));

               color4 =   QColor ( image.pixel(x-1,y));
               color5 =   QColor ( image.pixel(x+1,y));

               color6 =   QColor ( image.pixel(x-1,y+1));
               color7=   QColor ( image.pixel(x,y+1));
               color8 =   QColor ( image.pixel(x+1,y+1));
               r = abs(color1.red() + color2.red() * 2 + color3.red() - color6.red() - color7.red() * 2 - color8.red());
               g = abs(color1.green() + color2.green() * 2 + color3.green() - color6.green() - color7.green() * 2 - color8.green());
               b = abs(color1.blue() + color2.blue() * 2 + color3.blue() - color6.blue() - color7.blue() * 2 - color8.blue());
               rgb = r + g + b;

               r1 = abs(color1.red() + color4.red() * 2 + color6.red() - color3.red() - color5.red() * 2 - color8.red());
               g1= abs(color1.green() + color4.green() * 2 + color6.green() - color3.green() - color5.green() * 2 - color8.green());
               b1 = abs(color1.blue() + color4.blue() * 2 + color6.blue() - color3.blue() - color5.blue() * 2 - color8.blue());
               rgb1 = r1 + g1 + b1;
              if(type == 0)
              {
                  if (rgb > rgb1)
                      a = rgb;
                  else
                      a = rgb1;
              }
              else if(type == 1)
              {
               a = (rgb + rgb1)/2;
              }
               a = a * scale;
               a = a>255?255:a;

               newImage->setPixel(x,y,qRgb(a,a,a));
           }
}
        ui->label->setPixmap(QPixmap::fromImage(*newImage));
}

void MainWindow::on_pushButton_6_clicked()
{
    const QPixmap *img = ui->label->pixmap();
    QImage origin=img->toImage();
    int dir[9][2]={{0,0},{0,1},{0,-1},{-1,0},{-1,1},{-1,-1},{1,1},{1,0},{1,-1}};
       QImage  newImage =QImage(origin.width(), origin.height(), QImage::Format_ARGB32);
       for(int y=0;y<newImage.height();y++){
           for(int x=0;x<newImage.width();x++){
               int count=0;
               int togreen=0;
               int tored=0;
               int toblue=0;
               for(int i=0;i<9;i++){
                   if(x+dir[i][0]>=0&&x+dir[i][0]<newImage.width()&&y+dir[i][1]>=0&&y+dir[i][1]<newImage.height()){
                       count++;
                       QRgb point=origin.pixel(x+dir[i][0],y+dir[i][1]);
                       togreen+=qGreen(point);
                       tored+=qRed(point);
                       toblue+=qBlue(point);
                   }
               }
                togreen=togreen/count;
                toblue=toblue/count;
                tored=tored/count;
               newImage.setPixel(x,y, qRgb(tored,togreen,toblue));
            }
           }
       QPixmap pixmap = QPixmap::fromImage(newImage);
       pixmap=pixmap.scaled(ui->label->size());
       ui->label->setPixmap(pixmap);
}

void MainWindow::on_pushButton_8_clicked()
{
    const QPixmap *img = ui->label->pixmap();
    QImage s=img->toImage();
    QImage *newImage =new QImage(s.width(),s.height(),QImage::Format_RGB32);
    for (int y=0;y<newImage->height();y++) {
        QRgb *line =(QRgb *)s.scanLine(y);
        for (int x=0;x<newImage->width();x++) {
            int aver=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;


            newImage->setPixel(x,y,qRgb(aver,aver,aver));
        }
    }
     ui->label->setPixmap(QPixmap::fromImage(*newImage));
}

void MainWindow::on_pushButton_9_clicked()
{
    const QPixmap *img = ui->label->pixmap();
    QImage Img=img->toImage();
    QImage *newImage =new QImage(Img.width(),Img.height(),QImage::Format_RGB32);
    for (int y=0;y<newImage->height();y++) {
               QRgb *line =(QRgb *)Img.scanLine(y);
               for (int x=0;x<newImage->width();x++) {
                   int aver1=qRed(line[x]);
                   int aver2=qGreen(line[x]);
                   int aver3=qBlue(line[x]);


                   newImage->setPixel(x,y,qRgb(aver1,aver2,aver3));
               }
           }

    QPainter painter (newImage);
    int fontsize = 25,spacing = 10;
    QString text="孙海烽";
    QFont font("微软雅黑", fontsize,QFont::Thin);
    font.setLetterSpacing(QFont::AbsoluteSpacing, spacing);painter. setFont(font);
    painter. setPen ( QColor ( 150,150,150)) ;
    painter.translate( newImage->width() / 2,-newImage->width() / 2);//调整位置
    painter.rotate(45);
    int squareEdgesize = newImage->width() * sin(45.0) + newImage->height() * sin(45.0);//对角线长度
    int hCount = squareEdgesize / ((fontsize + spacing) * (text.size() + 1)) + 1;int x = squareEdgesize / hCount + (fontsize + spacing) * 3;
    int y = x / 2;
    for (int i = 0; i < hCount; i++){
    for (int j = 0; j < hCount* 2;j++){
    painter.drawText(x * i, y * j,text);
    }
    }
    ui->label->setPixmap(QPixmap::fromImage(*newImage));

}

void MainWindow::on_pushButton_10_clicked()
{

     const QPixmap *img = ui->label->pixmap();
     int threshold=i;
     QImage rgbImage=img->toImage();
      QSize size = rgbImage.size();
      QImage binaryImage(size, QImage::Format_RGB32);
      int width = size.width();
      int height = size.width();
      for(int i = 0; i < size.width(); i++)
        for(int j = 0; j < size.height(); j++)
        {
          QRgb pixel = rgbImage.pixel(i, j);
          int r = qRed(pixel) * 0.3;
          int g = qGreen(pixel) * 0.59;
          int b = qBlue(pixel) * 0.11;
          int rgb = r + g + b;//先把图像灰度化，转化为灰度图像
          if (rgb > threshold)//然后按某一阀值进行二值化
          {
            rgb = 255;
          }else
          {
            rgb = 0;
          }
          QRgb newPixel = qRgb(rgb, rgb, rgb);
          binaryImage.setPixel(i, j, newPixel);
        }

       ui->label->setPixmap(QPixmap::fromImage(binaryImage));
    }


void MainWindow::on_Slider_valueChanged(int value)
{

    i=value;

     int threshold=value;
     QImage rgbImage=abc;
      QSize size = rgbImage.size();
      QImage binaryImage(size, QImage::Format_RGB32);
      int width = size.width();
      int height = size.width();
      for(int i = 0; i < size.width(); i++)
        for(int j = 0; j < size.height(); j++)
        {
          QRgb pixel = rgbImage.pixel(i, j);
          int r = qRed(pixel) * 0.3;
          int g = qGreen(pixel) * 0.59;
          int b = qBlue(pixel) * 0.11;
          int rgb = r + g + b;//先把图像灰度化，转化为灰度图像
          if (rgb > threshold)//然后按某一阀值进行二值化
          {
            rgb = 255;
          }else
          {
            rgb = 0;
          }
          QRgb newPixel = qRgb(rgb, rgb, rgb);
          binaryImage.setPixel(i, j, newPixel);
        }

       ui->label->setPixmap(QPixmap::fromImage(binaryImage));
    }


void MainWindow::on_pushButton_12_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(abc));
}
