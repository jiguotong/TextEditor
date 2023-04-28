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
    //���ÿ�����������
    QPixmap pixmap(":/textEditor/res/splash.png");   //������������
    pixmap = pixmap.scaled(250, 250, Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap);
    splash.show();   //��ʾ������ͼ��
    a.processEvents();   //ʹ�ó�������ʾ���������ͬʱ���ܹ���Ӧ�����¼�
    Sleep(1000);

    // ���ν���
    char* openFilePath = NULL;
    if (argc == 2)
        openFilePath = argv[1];
    Mainwindow w(openFilePath);
    w.show();

    splash.finish(&w);  //���������������

    return a.exec();
}
//Qt C++ ���ȫ
//https://doc.qt.io/qt-5/classes.html