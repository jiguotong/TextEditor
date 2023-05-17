/********************************************************************************
** Form generated from reading UI file 'FindWidgetitzNSx.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FINDWIDGETITZNSX_H
#define FINDWIDGETITZNSX_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindWidgetClass
{
public:
    QWidget *centralWidget;
    QTextEdit *editorFind;
    QPushButton *btnNextString;
    QPushButton *btnPreString;
    QPushButton *btnClose;
    QTextEdit *editorReplace;
    QPushButton *btnReplace;
    QPushButton *btnReplaceAll;
    QPushButton *btnOpenReplace;

    void setupUi(QMainWindow *FindWidgetClass)
    {
        if (FindWidgetClass->objectName().isEmpty())
            FindWidgetClass->setObjectName(QString::fromUtf8("FindWidgetClass"));
        FindWidgetClass->resize(600, 119);
        FindWidgetClass->setMinimumSize(QSize(10, 10));
        FindWidgetClass->setMaximumSize(QSize(1000, 1000));
        centralWidget = new QWidget(FindWidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        editorFind = new QTextEdit(centralWidget);
        editorFind->setObjectName(QString::fromUtf8("editorFind"));
        editorFind->setGeometry(QRect(60, 19, 231, 31));
        btnNextString = new QPushButton(centralWidget);
        btnNextString->setObjectName(QString::fromUtf8("btnNextString"));
        btnNextString->setGeometry(QRect(400, 23, 75, 23));
        btnPreString = new QPushButton(centralWidget);
        btnPreString->setObjectName(QString::fromUtf8("btnPreString"));
        btnPreString->setGeometry(QRect(320, 23, 75, 23));
        btnClose = new QPushButton(centralWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(490, 23, 75, 23));
        editorReplace = new QTextEdit(centralWidget);
        editorReplace->setObjectName(QString::fromUtf8("editorReplace"));
        editorReplace->setGeometry(QRect(60, 70, 231, 31));
        btnReplace = new QPushButton(centralWidget);
        btnReplace->setObjectName(QString::fromUtf8("btnReplace"));
        btnReplace->setGeometry(QRect(320, 70, 81, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(12);
        btnReplace->setFont(font);
        btnReplaceAll = new QPushButton(centralWidget);
        btnReplaceAll->setObjectName(QString::fromUtf8("btnReplaceAll"));
        btnReplaceAll->setGeometry(QRect(410, 70, 101, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        btnReplaceAll->setFont(font1);
        btnOpenReplace = new QPushButton(centralWidget);
        btnOpenReplace->setObjectName(QString::fromUtf8("btnOpenReplace"));
        btnOpenReplace->setGeometry(QRect(10, 19, 30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8("res/replace.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpenReplace->setIcon(icon);
        FindWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(FindWidgetClass);

        QMetaObject::connectSlotsByName(FindWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *FindWidgetClass)
    {
        FindWidgetClass->setWindowTitle(QCoreApplication::translate("FindWidgetClass", "FindWidget", nullptr));
        btnNextString->setText(QCoreApplication::translate("FindWidgetClass", "\344\270\213\344\270\200\344\270\252", nullptr));
        btnPreString->setText(QCoreApplication::translate("FindWidgetClass", "\344\270\212\344\270\200\344\270\252", nullptr));
        btnClose->setText(QCoreApplication::translate("FindWidgetClass", "\345\205\263\351\227\255", nullptr));
        btnReplace->setText(QCoreApplication::translate("FindWidgetClass", "Replace", nullptr));
        btnReplaceAll->setText(QCoreApplication::translate("FindWidgetClass", "Replace all", nullptr));
        btnOpenReplace->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FindWidgetClass: public Ui_FindWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FINDWIDGETITZNSX_H
