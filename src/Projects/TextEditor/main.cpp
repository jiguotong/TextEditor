#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QMessageBox>
#include <QTime>
#include <windows.h>
#define ZY 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*时间有效期为3天，三天后不可用！*/
    QDateTime baseTime = QDateTime::fromString("2023-05-17 00:00:00", "yyyy-MM-dd hh:mm:ss");       // 规定一个初始化基准时间
    QDateTime currentTime = QDateTime::currentDateTime();                                           //获取系统当前的时间
    int startTime = baseTime.toTime_t();        //将当前时间转为时间戳
    int endTime = currentTime.toTime_t();       //将当前时间转为时间戳
    if (endTime - startTime > 2592000) {
        QMessageBox::warning(NULL, "Error", "Time permission exceeded! Please contact the developer!");
        return -1;
    }

    // 进入程序
    for (size_t i = 0; i < argc; i++){
        printf("argv[%d]:%s\n",i, argv[i]);
    }
    
#ifdef ZY
    QPixmap pixmap(":/textEditor/res/splash_zy.png");   //设置启动画面
#else
    //设置开机启动动画
    QPixmap pixmap(":/textEditor/res/splash.png");   //设置启动画面
#endif // ZY
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