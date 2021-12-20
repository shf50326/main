#include "mainwindow.h"

#include <QApplication>
#include<QTranslator>
#include<QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("../shf-5/shf-5_CN.qm" );
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
