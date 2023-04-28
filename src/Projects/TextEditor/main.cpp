#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    for (size_t i = 0; i < argc; i++){
        printf("argv[%d]:%s\n",i, argv[i]);
    }
    //设置开机启动动画
    QPixmap pixmap(":/textEditor/res/splash.png");   //设置启动画面
    pixmap = pixmap.scaled(250, 250, Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap);
    splash.show();   //显示此启动图像
    a.processEvents();   //使得程序在显示启动画面的同时还能够响应其他事件
    Sleep(1000);

    // 传参进入
    char* openFilePath = NULL;
    if (argc == 2)
        openFilePath = argv[1];
    Mainwindow w(openFilePath);
    w.show();

    splash.finish(&w);  //程序启动画面完成

    return a.exec();
}
//Qt C++ 类大全
//https://doc.qt.io/qt-5/classes.html