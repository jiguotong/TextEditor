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

    /*ʱ����Ч��Ϊ3�죬����󲻿��ã�*/
    QDateTime baseTime = QDateTime::fromString("2023-05-17 00:00:00", "yyyy-MM-dd hh:mm:ss");       // �涨һ����ʼ����׼ʱ��
    QDateTime currentTime = QDateTime::currentDateTime();                                           //��ȡϵͳ��ǰ��ʱ��
    int startTime = baseTime.toTime_t();        //����ǰʱ��תΪʱ���
    int endTime = currentTime.toTime_t();       //����ǰʱ��תΪʱ���
    if (endTime - startTime > 2592000) {
        QMessageBox::warning(NULL, "Error", "Time permission exceeded! Please contact the developer!");
        return -1;
    }

    // �������
    for (size_t i = 0; i < argc; i++){
        printf("argv[%d]:%s\n",i, argv[i]);
    }
    
#ifdef ZY
    QPixmap pixmap(":/textEditor/res/splash_zy.png");   //������������
#else
    //���ÿ�����������
    QPixmap pixmap(":/textEditor/res/splash.png");   //������������
#endif // ZY
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