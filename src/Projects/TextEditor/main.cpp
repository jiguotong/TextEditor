#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //���ÿ�����������
    QPixmap pixmap(":/textEditor/res/splash.png");   //������������
    pixmap = pixmap.scaled(500, 500, Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap);
    splash.show();   //��ʾ������ͼ��
    a.processEvents();   //ʹ�ó�������ʾ���������ͬʱ���ܹ���Ӧ�����¼�

    Sleep(4000);
    Mainwindow w;
    w.show();

    splash.finish(&w);  //���������������

    return a.exec();
}
//Qt C++ ���ȫ
//https://doc.qt.io/qt-5/classes.html