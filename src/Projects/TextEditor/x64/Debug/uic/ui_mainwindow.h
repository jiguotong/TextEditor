/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainwindowClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *MainwindowClass)
    {
        if (MainwindowClass->objectName().isEmpty())
            MainwindowClass->setObjectName(QString::fromUtf8("MainwindowClass"));
        MainwindowClass->resize(600, 400);
        centralWidget = new QWidget(MainwindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainwindowClass->setCentralWidget(centralWidget);

        retranslateUi(MainwindowClass);

        QMetaObject::connectSlotsByName(MainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainwindowClass)
    {
        MainwindowClass->setWindowTitle(QCoreApplication::translate("MainwindowClass", "Mainwindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainwindowClass: public Ui_MainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
